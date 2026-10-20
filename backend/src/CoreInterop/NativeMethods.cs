using System;
using System.Runtime.InteropServices;

namespace CoreInterop
{
    public static class NativeMethods
    {
        private const string LibName = "libfire_protection_core";

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern double fp_gpm_to_lpm(double gpm);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern double fp_lpm_to_gpm(double lpm);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern double fp_psi_to_bar(double psi);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern double fp_bar_to_psi(double bar);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern double fp_calculate_hazen_williams_loss(double flowGpm, double lengthFt, double cFactor, double diameterInch);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern double fp_calculate_sprinkler_flow(double kFactor, double pressurePsi);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr fp_solve_hydraulic_network_json(string inputJson);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr fp_calculate_nac_voltage_drop_json(string inputJson);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr fp_calculate_battery_capacity_json(string inputJson);

        [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void fp_free_string(IntPtr str);

        public static string MarshalAndFree(IntPtr ptr)
        {
            if (ptr == IntPtr.Zero) return string.Empty;
            try
            {
                return Marshal.PtrToStringAnsi(ptr) ?? string.Empty;
            }
            finally
            {
                fp_free_string(ptr);
            }
        }
    }
}
