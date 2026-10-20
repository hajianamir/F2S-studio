using System;
using System.IO;
using System.Collections.Generic;
using Domain;
using Xbim.Ifc;
using Xbim.Ifc4.Interfaces;

namespace Infrastructure
{
    public class Ifc4BimAdapter
    {
        public FireProtectionProject ImportIfc4File(string ifcFilePath, string projectName)
        {
            var project = new FireProtectionProject { Name = projectName };
            using var model = IfcStore.Open(ifcFilePath);

            int pipeIndex = 1;
            foreach (var pipeSegment in model.Instances.OfType<IIfcPipeSegment>())
            {
                project.Pipes.Add(new NetworkPipe
                {
                    Id = $"P_IFC_{pipeIndex++}",
                    StartNodeId = $"N_{pipeIndex}_A",
                    EndNodeId = $"N_{pipeIndex}_B",
                    InternalDiameterInch = 2.0,
                    LengthFeet = 10.0,
                    CFactor = 120.0
                });
            }

            int sprinklerIndex = 1;
            foreach (var terminal in model.Instances.OfType<IIfcFlowTerminal>())
            {
                project.Nodes.Add(new NetworkNode
                {
                    Id = $"SPK_IFC_{sprinklerIndex++}",
                    ElevationFeet = 10.0,
                    KFactor = 5.6,
                    MinimumPressurePsi = 7.0
                });
            }

            return project;
        }
    }
}
