using System;
using Xunit;
using CoreInterop;
using Domain;

namespace BackendTests
{
    public class InteropTests
    {
        [Fact]
        public void TestUnitConversion()
        {
            double lpm = NativeMethods.fp_gpm_to_lpm(100.0);
            Assert.True(lpm > 370.0 && lpm < 380.0);
        }

        [Fact]
        public void TestDomainProjectCreation()
        {
            var proj = new FireProtectionProject { Name = "Test Fire System" };
            Assert.NotNull(proj.Id);
            Assert.Equal("NFPA13-2022", proj.StandardVersion);
        }
    }
}
