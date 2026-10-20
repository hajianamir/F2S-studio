using System;
using System.Collections.Generic;

namespace Domain
{
    public class FireProtectionProject
    {
        public Guid Id { get; set; } = Guid.NewGuid();
        public string Name { get; set; } = string.Empty;
        public string StandardVersion { get; set; } = "NFPA13-2022";
        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
        public List<NetworkNode> Nodes { get; set; } = new();
        public List<NetworkPipe> Pipes { get; set; } = new();
    }
}
