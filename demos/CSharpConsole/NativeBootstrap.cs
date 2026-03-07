//using System.Reflection;
//using System.Runtime.InteropServices;

///// <summary>
///// FUTURE* Provides native library resolution for the colors library across supported platforms.
///// </summary>
///// <remarks>Registers a custom DllImport resolver to map the logical library name to the appropriate platform-specific native library file.</remarks>
//internal static class NativeBootstrap
//{
//    private const string LogicalName = "colors.dev";
//    public static string LibaryName { get; set; } = "colors.dev";

//    static NativeBootstrap()
//    {
//        NativeLibrary.SetDllImportResolver(typeof(NativeBootstrap).Assembly, Resolve);
//    }

//    private static nint Resolve(string libraryName, Assembly assembly, DllImportSearchPath? searchPath)
//    {
//        if (!string.Equals(libraryName, LogicalName, StringComparison.OrdinalIgnoreCase))
//            return 0;

//        string mapped =
//            RuntimeInformation.IsOSPlatform(OSPlatform.Windows) ? "colors.dev.dll" :
//            RuntimeInformation.IsOSPlatform(OSPlatform.OSX) ? "libcolors.dev.dylib" :
//                                                                 "libcolors.dev.so";

//        // Let .NET search in normal places (including runtimes/<rid>/native)
//        if (NativeLibrary.TryLoad(mapped, assembly, searchPath, out var handle))
//            return handle;

//        // Fallback: try logical name too
//        if (NativeLibrary.TryLoad(libraryName, assembly, searchPath, out handle))
//            return handle;

//        return 0;
//    }
//}