namespace Domain
{
    public class NetworkNode
    {
        public string Id { get; set; } = string.Empty;
        public double ElevationFeet { get; set; }
        public double KFactor { get; set; }
        public double MinimumPressurePsi { get; set; }
        public double FixedDemandGpm { get; set; }
        public bool IsSource { get; set; }
    }
}
