namespace Domain
{
    public class NetworkPipe
    {
        public string Id { get; set; } = string.Empty;
        public string StartNodeId { get; set; } = string.Empty;
        public string EndNodeId { get; set; } = string.Empty;
        public double InternalDiameterInch { get; set; }
        public double LengthFeet { get; set; }
        public double CFactor { get; set; } = 120.0;
        public double FittingEquivalentLengthFeet { get; set; }
    }
}
