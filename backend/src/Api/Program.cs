using System;
using System.Collections.Concurrent;
using CoreInterop;
using Domain;
using Infrastructure;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
builder.Services.AddSingleton<Ifc4BimAdapter>();

var app = builder.Build();

app.UseSwagger();
app.UseSwaggerUI();

var projects = new ConcurrentDictionary<Guid, FireProtectionProject>();
var calculationJobs = new ConcurrentDictionary<string, object>();

// Healthcheck
app.MapGet("/api/health", () => Results.Ok(new { status = "Healthy", timestamp = DateTime.UtcNow }));

// Hydraulic calculation endpoint via C++ P/Invoke
app.MapPost("/api/hydraulics/calculate", (FireProtectionProject proj) =>
{
    string jobId = Guid.NewGuid().ToString();
    string resultJson = NativeMethods.MarshalAndFree(NativeMethods.fp_solve_hydraulic_network_json("{}"));
    calculationJobs[jobId] = new { jobId, status = "Completed", result = resultJson };
    return Results.Ok(new { jobId, status = "Queued", pollingUrl = $"/api/jobs/{jobId}" });
});

// Job polling endpoint
app.MapGet("/api/jobs/{jobId}", (string jobId) =>
{
    if (calculationJobs.TryGetValue(jobId, out var jobInfo))
    {
        return Results.Ok(jobInfo);
    }
    return Results.NotFound(new { error = "Job not found" });
});

// Unit conversion endpoint
app.MapGet("/api/units/gpm-to-lpm", (double gpm) => Results.Ok(new { gpm, lpm = NativeMethods.fp_gpm_to_lpm(gpm) }));

app.Run();
