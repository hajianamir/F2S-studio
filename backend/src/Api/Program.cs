using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;
using CoreInterop;
using Domain;
using Infrastructure;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

var builder = WebApplication.CreateSlimBuilder(args);

builder.Services.ConfigureHttpJsonOptions(options =>
{
    options.SerializerOptions.TypeInfoResolverChain.Insert(0, AppJsonSerializerContext.Default);
});

var app = builder.Build();

var calculationJobs = new ConcurrentDictionary<string, CalculationJobResult>();

// Healthcheck
app.MapGet("/api/health", () => Results.Ok(new HealthResponse { Status = "Healthy", Timestamp = DateTime.UtcNow }));

// Multi-Standard Compliance Rule Verification Endpoint (NFPA 13, EN 12845, BS 9251)
app.MapGet("/api/rules/evaluate", (string standard, double coverageAreaSqFt, double pipeVelocityFps, double minPressurePsi) =>
{
    var evaluatedRules = new List<RuleEvaluationResult>();

    if (standard.Equals("EN12845", StringComparison.OrdinalIgnoreCase))
    {
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "EN12845-2020-13.2.1", IsCompliant = coverageAreaSqFt <= 226.0, Description = "Max coverage area <= 226 sq ft" });
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "EN12845-2020-13.2.2", IsCompliant = pipeVelocityFps <= 32.8, Description = "Max pipe velocity <= 32.8 ft/s" });
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "EN12845-2020-13.3.1", IsCompliant = minPressurePsi >= 7.25, Description = "Min operating pressure >= 7.25 psi" });
    }
    else if (standard.Equals("BS9251", StringComparison.OrdinalIgnoreCase))
    {
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "BS9251-2021-5.1.1", IsCompliant = coverageAreaSqFt <= 193.0, Description = "Max coverage area <= 193 sq ft" });
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "BS9251-2021-5.2.3", IsCompliant = minPressurePsi >= 7.0, Description = "Min operating pressure >= 7.0 psi" });
    }
    else // Default NFPA 13
    {
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "NFPA13-2022-8.6.2.1", IsCompliant = coverageAreaSqFt <= 225.0, Description = "Max coverage area <= 225 sq ft" });
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "NFPA13-2022-10.2.2", IsCompliant = pipeVelocityFps <= 32.0, Description = "Max pipe velocity <= 32.0 ft/s" });
        evaluatedRules.Add(new RuleEvaluationResult { RuleId = "NFPA13-2022-10.2.1", IsCompliant = minPressurePsi >= 7.0, Description = "Min operating pressure >= 7.0 psi" });
    }

    return Results.Ok(new MultiStandardEvaluationResponse
    {
        Standard = standard,
        EvaluatedRules = evaluatedRules
    });
});

// Hydraulic calculation endpoint via C++ P/Invoke
app.MapPost("/api/hydraulics/calculate", (FireProtectionProject proj) =>
{
    string jobId = Guid.NewGuid().ToString();
    string resultJson = NativeMethods.MarshalAndFree(NativeMethods.fp_solve_hydraulic_network_json("{}"));
    var jobRes = new CalculationJobResult { JobId = jobId, Status = "Completed", Result = resultJson };
    calculationJobs[jobId] = jobRes;
    return Results.Ok(new JobDispatchResponse { JobId = jobId, Status = "Queued", PollingUrl = $"/api/jobs/{jobId}" });
});

// Job polling endpoint
app.MapGet("/api/jobs/{jobId}", (string jobId) =>
{
    if (calculationJobs.TryGetValue(jobId, out var jobInfo))
    {
        return Results.Ok(jobInfo);
    }
    return Results.NotFound();
});

// Unit conversion endpoint
app.MapGet("/api/units/gpm-to-lpm", (double gpm) =>
{
    double lpmVal = NativeMethods.fp_gpm_to_lpm(gpm);
    return Results.Ok(new UnitConversionResponse { Gpm = gpm, Lpm = lpmVal });
});


// MEP Spatial Clash Detection Endpoint (Sprint 4 - 2A)
app.MapPost("/api/clash/detect", (ClashDetectionRequest req) =>
{
    var clashes = new List<ClashResponseItem>();
    // Hard clash simulation against HVAC duct
    clashes.Add(new ClashResponseItem
    {
        FireElementId = "P101_Riser",
        MepElementId = "D201_MainDuct",
        MepDiscipline = "HVAC",
        IsHardClash = true,
        ClearanceFt = 0.0
    });
    return Results.Ok(new ClashDetectionResponse
    {
        TotalClashesDetected = clashes.Count,
        HardClashCount = 1,
        SoftClashCount = 0,
        Clashes = clashes
    });
});

app.Run();

public class HealthResponse
{
    public string Status { get; set; } = string.Empty;
    public DateTime Timestamp { get; set; }
}

public class UnitConversionResponse
{
    public double Gpm { get; set; }
    public double Lpm { get; set; }
}

public class JobDispatchResponse
{
    public string JobId { get; set; } = string.Empty;
    public string Status { get; set; } = string.Empty;
    public string PollingUrl { get; set; } = string.Empty;
}

public class CalculationJobResult
{
    public string JobId { get; set; } = string.Empty;
    public string Status { get; set; } = string.Empty;
    public string Result { get; set; } = string.Empty;
}

public class RuleEvaluationResult
{
    public string RuleId { get; set; } = string.Empty;
    public bool IsCompliant { get; set; }
    public string Description { get; set; } = string.Empty;
}

public class MultiStandardEvaluationResponse
{
    public string Standard { get; set; } = string.Empty;
    public List<RuleEvaluationResult> EvaluatedRules { get; set; } = new();
}


public class ClashDetectionRequest
{
    public double ClearanceToleranceFt { get; set; } = 0.1;
}

public class ClashResponseItem
{
    public string FireElementId { get; set; } = string.Empty;
    public string MepElementId { get; set; } = string.Empty;
    public string MepDiscipline { get; set; } = string.Empty;
    public bool IsHardClash { get; set; }
    public double ClearanceFt { get; set; }
}

public class ClashDetectionResponse
{
    public int TotalClashesDetected { get; set; }
    public int HardClashCount { get; set; }
    public int SoftClashCount { get; set; }
    public List<ClashResponseItem> Clashes { get; set; } = new();
}

[JsonSerializable(typeof(HealthResponse))]
[JsonSerializable(typeof(ClashDetectionRequest))]
[JsonSerializable(typeof(ClashDetectionResponse))]
[JsonSerializable(typeof(ClashResponseItem))]
[JsonSerializable(typeof(List<ClashResponseItem>))]
[JsonSerializable(typeof(UnitConversionResponse))]
[JsonSerializable(typeof(JobDispatchResponse))]
[JsonSerializable(typeof(CalculationJobResult))]
[JsonSerializable(typeof(MultiStandardEvaluationResponse))]
[JsonSerializable(typeof(RuleEvaluationResult))]
[JsonSerializable(typeof(List<RuleEvaluationResult>))]
[JsonSerializable(typeof(FireProtectionProject))]
[JsonSerializable(typeof(NetworkNode))]
[JsonSerializable(typeof(NetworkPipe))]
internal partial class AppJsonSerializerContext : JsonSerializerContext
{
}
