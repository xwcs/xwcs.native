This library act as dll proxy to native c++ dll
Native c++ dll libbool_x86 or libbool_x64.dll will be loaded depending on OS where final application will be executed

.NET AnyCPU act as this: it will JIT assemblies depending on target paltform.

in order to obtain wanted functional effect we need force .NET to not find assembly and thus it will call
asembly resolve event. In this event we will force load of correct native dll

so all its done by this method:

1: we created libbool in 2 forms and we deploy it within xwcs.native project in libbool subfolder
2: we created managed wrapper xwcs.native with xwcs.native.boolexpr.Helper Class this class handle managed <-> native bridge
3: xwcs.native build fake dll  into its build dirs (xwcs.native_archproxy.dll) but it will not deploy it
4: when we setup reference to this assembly in xwcs.core project we set not copy to local (so dll from point 3 will not be deployed)
5: in post build event we copy xwcs.native_archproxy.dll intoo corect xwcs.native_x86.dll or xwcs.native_x64.dll)
6: in post build event we copy wrappers and all native libraries into final deploy directory
7: when xwcs.core will atempt to load xwcs.native_archproxy.dll it will fail and it will fire AppDomain.CurrentDomain.AssemblyResolve event
8: we did static core facade class  xwcs.core.Core which handle that event. it will check missed assembly name for presence "_archproxy" 
   place holder and it will replace it by x86 or x64 based on IntPtr size. And it will load corect dll

NOTE: Pay attention if you are building Release or Debug, cause both share folder for x86 and x64 builds, so if you switch from 
      Release to Debug and vs. you need build also xwcs.native

BUILD:

There is different post build step in case of Deploy config!!!! it will push Nuget!!!
1: Release x64
2: Release x86 => version number during nuget deploy
3: Deploy (does not mother) -> will produce nuget and push it