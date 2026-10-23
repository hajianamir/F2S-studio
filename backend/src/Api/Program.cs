using System;
using System.Collections.Concurrent;
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

[JsonSerializable(typeof(HealthResponse))]
[JsonSerializable(typeof(UnitConversionResponse))]
[JsonSerializable(typeof(JobDispatchResponse))]
[JsonSerializable(typeof(CalculationJobResult))]
[JsonSerializable(typeof(FireProtectionProject))]
[JsonSerializable(typeof(NetworkNode))]
[JsonSerializable(typeof(NetworkPipe))]
internal partial class AppJsonSerializerContext : JsonSerializerContext
{
}
