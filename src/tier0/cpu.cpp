//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
#include "pch_tier0.h"

#if defined(_WIN32) && !defined(_X360)
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include "cputopology.h"
#elif defined( PLATFORM_OSX )
#include <sys/sysctl.h>
#endif

#ifndef _PS3
#include "tier0_strtools.h"
#endif

//#include "tier1/strtools.h" // this is included for the definition of V_isspace()
#ifdef PLATFORM_WINDOWS_PC
#include <intrin.h>
#endif

// NOTE: This has to be the last file included!
#include "tier0/memdbgon.h"

const tchar* GetProcessorVendorId();
const tchar* GetProcessorBrand();

struct CpuIdResult_t
{
	unsigned long eax;
	unsigned long ebx;
	unsigned long ecx;
	unsigned long edx;

	void Reset()
	{
		eax = ebx = ecx = edx = 0;
	}
};


static bool cpuid( unsigned long function, CpuIdResult_t &out )
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#elif defined(GNUC)
	unsigned long out_eax,out_ebx,out_ecx,out_edx;
#ifdef PLATFORM_64BITS
	asm("mov %%rbx, %%rsi\n\t"
		"cpuid\n\t"
		"xchg %%rsi, %%rbx"
		: "=a" (out_eax),
		  "=S" (out_ebx),
		  "=c" (out_ecx),
		  "=d" (out_edx)
		: "a" (function) 
	);
#else
	asm("mov %%ebx, %%esi\n\t"
		"cpuid\n\t"
		"xchg %%esi, %%ebx"
		: "=a" (out_eax),
		  "=S" (out_ebx),
		  "=c" (out_ecx),
		  "=d" (out_edx)
		: "a" (function) 
	);
#endif
	out.eax = out_eax;
	out.ebx = out_ebx;
	out.ecx = out_ecx;
	out.edx = out_edx;	

	return true;
#elif defined(_WIN64)
	int pCPUInfo[4];
	__cpuid( pCPUInfo, (int)function );
	out.eax = pCPUInfo[0];
	out.ebx = pCPUInfo[1];
	out.ecx = pCPUInfo[2];
	out.edx = pCPUInfo[3];
	return true;
#else
	bool retval = true;
	unsigned long out_eax = 0, out_ebx = 0, out_ecx = 0, out_edx = 0;
	_asm pushad;

	__try
	{
        _asm
		{
			xor edx, edx		// Clue the compiler that EDX & others is about to be used. 
			xor ecx, ecx
			xor ebx, ebx        // <Sergiy> Note: if I don't zero these out, cpuid sometimes won't work, I didn't find out why yet
            mov eax, function   // set up CPUID to return processor version and features
								//      0 = vendor string, 1 = version info, 2 = cache info
            cpuid				// code bytes = 0fh,  0a2h
            mov out_eax, eax	// features returned in eax
            mov out_ebx, ebx	// features returned in ebx
            mov out_ecx, ecx	// features returned in ecx
            mov out_edx, edx	// features returned in edx
		}
    } 
	__except(EXCEPTION_EXECUTE_HANDLER) 
	{ 
		retval = false; 
	}

	out.eax = out_eax;
	out.ebx = out_ebx;
	out.ecx = out_ecx;
	out.edx = out_edx;

	_asm popad

	return retval;
#endif
}


static bool cpuidex( unsigned long function, unsigned long subfunction, CpuIdResult_t &out )
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#elif defined(GNUC)
	unsigned long out_eax, out_ebx, out_ecx, out_edx;

	asm( "mov %%ebx, %%esi\n\t"
		"cpuid\n\t"
		"xchg %%esi, %%ebx"
		: "=a" ( out_eax ),
		"=S" ( out_ebx ),
		"=c" ( out_ecx ),
		"=d" ( out_edx )
		: "a" ( function ),
		  "c" ( subfunction )
		);

	out.eax = out_eax;
	out.ebx = out_ebx;
	out.ecx = out_ecx;
	out.edx = out_edx;

	return true;
#elif defined(_WIN64)
	int pCPUInfo[ 4 ];
	__cpuidex( pCPUInfo, ( int )function, ( int )subfunction );
	out.eax = pCPUInfo[ 0 ];
	out.ebx = pCPUInfo[ 1 ];
	out.ecx = pCPUInfo[ 2 ];
	out.edx = pCPUInfo[ 3 ];
	return false;
#else
	bool retval = true;
	unsigned long out_eax = 0, out_ebx = 0, out_ecx = 0, out_edx = 0;
	_asm pushad;

	__try
	{
		_asm
		{
			xor edx, edx		// Clue the compiler that EDX & others is about to be used. 
			mov ecx, subfunction
			xor ebx, ebx        // <Sergiy> Note: if I don't zero these out, cpuid sometimes won't work, I didn't find out why yet
			mov eax, function   // set up CPUID to return processor version and features
			//      0 = vendor string, 1 = version info, 2 = cache info
			cpuid				// code bytes = 0fh,  0a2h
			mov out_eax, eax	// features returned in eax
			mov out_ebx, ebx	// features returned in ebx
			mov out_ecx, ecx	// features returned in ecx
			mov out_edx, edx	// features returned in edx
		}
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		retval = false;
	}

	out.eax = out_eax;
	out.ebx = out_ebx;
	out.ecx = out_ecx;
	out.edx = out_edx;

	_asm popad

	return retval;
#endif
}


static CpuIdResult_t cpuid( unsigned long function )
{
	CpuIdResult_t out;
	if ( !cpuid( function, out ) )
	{
		out.Reset();
	}
	return out;
}

static CpuIdResult_t cpuidex( unsigned long function, unsigned long subfunction )
{
	CpuIdResult_t out;
	if ( !cpuidex( function, subfunction, out ) )
	{
		out.Reset();
	}
	return out;
}


static bool CheckSSETechnology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return true;
#else
    return ( cpuid( 1 ).edx & 0x2000000L ) != 0;
#endif
}

static bool CheckSSE2Technology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
    return ( cpuid( 1 ).edx & 0x04000000 ) != 0;
#endif
}

bool CheckSSE3Technology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	return ( cpuid( 1 ).ecx & 0x00000001 ) != 0;	// bit 1 of ECX
#endif
}

bool CheckSSSE3Technology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	// SSSE 3 is implemented by both Intel and AMD
	// detection is done the same way for both vendors
	return ( cpuid( 1 ).ecx & ( 1 << 9 ) ) != 0;	// bit 9 of ECX
#endif
}

bool CheckSSE41Technology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	// SSE 4.1 is implemented by both Intel and AMD
	// detection is done the same way for both vendors

	return ( cpuid( 1 ).ecx & ( 1 << 19 ) ) != 0;	// bit 19 of ECX
#endif
}

bool CheckSSE42Technology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	// SSE4.2 is an Intel-only feature

	const char *pchVendor = GetProcessorVendorId();
	if ( 0 != V_tier0_stricmp( pchVendor, "GenuineIntel" ) )
		return false;

	return ( cpuid( 1 ).ecx & ( 1 << 20 ) ) != 0;	// bit 20 of ECX
#endif
}


bool CheckSSE4aTechnology( void )
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	// SSE 4a is an AMD-only feature

	const char *pchVendor = GetProcessorVendorId();
	if ( 0 != V_tier0_stricmp( pchVendor, "AuthenticAMD" ) )
		return false;

	return ( cpuid( 1 ).ecx & ( 1 << 6 ) ) != 0;	// bit 6 of ECX
#endif
}


static bool Check3DNowTechnology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	if ( cpuid( 0x80000000 ).eax > 0x80000000L )
    {
		return ( cpuid( 0x80000001 ).eax & ( 1 << 31 ) ) != 0;
    }
    return false;
#endif
}

static bool CheckCMOVTechnology()
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	return ( cpuid( 1 ).edx & ( 1 << 15 ) ) != 0;
#endif
}

static bool CheckFCMOVTechnology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	return ( cpuid( 1 ).edx & ( 1 << 16 ) ) != 0;
#endif
}

static bool CheckRDTSCTechnology(void)
{
#if defined( _X360 ) || defined( _PS3 ) || defined( __aarch64__ )
	return false;
#else
	return ( cpuid( 1 ).edx & 0x10 ) != 0;
#endif
}


static tchar s_CpuVendorID[16] = "unknown";

bool s_bCpuVendorIdInitialized = false;

union CpuBrand_t
{
	CpuIdResult_t cpuid[ 3 ];
	char name[ 49 ];
};
CpuBrand_t s_CpuBrand;

bool s_bCpuBrandInitialized = false;

// Return the Processor's vendor identification string, or "Generic_x86" if it doesn't exist on this CPU
const tchar* GetProcessorVendorId()
{
#if defined( _X360 ) || defined( _PS3 )
	return "PPC";
#elif defined( __aarch64__ )
	return "ARM";
#else
	if ( s_bCpuVendorIdInitialized )
	{
		return s_CpuVendorID;
	}

	s_bCpuVendorIdInitialized = true;

	CpuIdResult_t cpuid0 = cpuid( 0 );
	
	memset( s_CpuVendorID, 0, sizeof(s_CpuVendorID) );

	if ( !cpuid0.eax )
	{
		// weird...
		if ( IsPC() )
		{
			_tcscpy( s_CpuVendorID, _T( "Generic_x86" ) ); 
		}
		else if ( IsX360() )
		{
			_tcscpy( s_CpuVendorID, _T( "PowerPC" ) ); 
		}
	}
	else
	{
		memcpy( s_CpuVendorID + 0, &( cpuid0.ebx ), sizeof( cpuid0.ebx ) );
		memcpy( s_CpuVendorID + 4, &( cpuid0.edx ), sizeof( cpuid0.edx ) );
		memcpy( s_CpuVendorID + 8, &( cpuid0.ecx ), sizeof( cpuid0.ecx ) );
	}

	return s_CpuVendorID;
#endif
}

const tchar* GetProcessorBrand()
{
#if defined( _X360 )
	return "Xenon";
#elif defined( _PS3 )
	return "Cell Broadband Engine";
#elif defined( __aarch64__ )
	return "ARM";
#else
	if ( s_bCpuBrandInitialized )
	{
		return s_CpuBrand.name;
	}
	s_bCpuBrandInitialized = true;

	memset( &s_CpuBrand, 0, sizeof( s_CpuBrand ) );

	const char *pchVendor = GetProcessorVendorId();
	if ( 0 == V_tier0_stricmp( pchVendor, "GenuineIntel" ) )
	{
		// Intel brand string
		if ( cpuid( 0x80000000 ).eax >= 0x80000004 )
		{
			s_CpuBrand.cpuid[ 0 ] = cpuid( 0x80000002 );
			s_CpuBrand.cpuid[ 1 ] = cpuid( 0x80000003 );
			s_CpuBrand.cpuid[ 2 ] = cpuid( 0x80000004 );
		}
	}
	return s_CpuBrand.name;

#endif
}

// Returns non-zero if Hyper-Threading Technology is supported on the processors and zero if not.
// If it's supported, it does not mean that it's been enabled. So we test another flag to see if it's enabled
// See Intel Processor Identification and the CPUID instruction Application Note 485
// http://www.intel.com/Assets/PDF/appnote/241618.pdf
static bool HTSupported(void)
{
#if ( defined( _X360 ) || defined( _PS3 ) )
	// not entirtely sure about the semantic of HT support, it being an intel name
	// are we asking about HW threads or HT?
	return true;
#elif defined( __aarch64__ )
	return false;
#else
	enum {
		HT_BIT		 = 0x10000000,  // EDX[28] - Bit 28 set indicates Hyper-Threading Technology is supported in hardware.
		FAMILY_ID     = 0x0f00,      // EAX[11:8] - Bit 11 thru 8 contains family processor id
		EXT_FAMILY_ID = 0x0f00000,	// EAX[23:20] - Bit 23 thru 20 contains extended family  processor id
		FAMILY_ID_386 = 0x0300,
		FAMILY_ID_486 = 0x0400,     // EAX[8:12]  -  486, 487 and overdrive
		FAMILY_ID_PENTIUM = 0x0500, //               Pentium, Pentium OverDrive  60 - 200
		FAMILY_ID_PENTIUM_PRO = 0x0600,//            P Pro, P II, P III, P M, Celeron M, Core Duo, Core Solo, Core2 Duo, Core2 Extreme, P D, Xeon model F,
		                               //            also 45-nm : Intel Atom, Core i7, Xeon MP ; see Intel Processor Identification and the CPUID instruction pg 20,21
		                               
		FAMILY_ID_EXTENDED = 0x0F00 //               P IV, Xeon, Celeron D, P D, 
	};

	// this works on both newer AMD and Intel CPUs
	CpuIdResult_t cpuid1 = cpuid( 1 );

	// <Sergiy> Previously, we detected P4 specifically; now, we detect GenuineIntel with HT enabled in general
	// if (((cpuid1.eax & FAMILY_ID) ==  FAMILY_ID_EXTENDED) || (cpuid1.eax & EXT_FAMILY_ID))
	
	//  Check to see if this is an Intel Processor with HT or CMT capability , and if HT/CMT is enabled
	// ddk: This codef is actually correct: see example code at software.intel.com/en-us/articles/multi-core-detect/
	return ( cpuid1.edx & HT_BIT ) != 0 && // Genuine Intel Processor with Hyper-Threading Technology implemented
		( ( cpuid1.ebx >> 16 ) & 0xFF ) > 1; // Hyper-Threading OR Core Multi-Processing has been enabled
#endif
}

// Returns the number of logical processors per physical processors.
static uint8 LogicalProcessorsPerPackage(void)
{
#if defined( _X360 )
	return 2;
#elif defined( __aarch64__ )
	return 1;
#else
	// EBX[23:16] indicate number of logical processors per package
	const unsigned NUM_LOGICAL_BITS = 0x00FF0000;

	if ( !HTSupported() ) 
		return 1; 

	return ( uint8 )( ( cpuid( 1 ).ebx & NUM_LOGICAL_BITS ) >> 16 );
#endif
}

#if defined(POSIX)
// Move this declaration out of the CalculateClockSpeed() function because
// otherwise clang warns that it is non-obvious whether it is a variable
// or a function declaration: [-Wvexing-parse]
uint64 CalculateCPUFreq(); // from cpu_linux.cpp
#endif

// Measure the processor clock speed by sampling the cycle count, waiting
// for some fraction of a second, then measuring the elapsed number of cycles.
static int64 CalculateClockSpeed()
{
#if defined( _X360 ) || defined(_PS3) || defined( __aarch64__ )
	// Xbox360 and PS3 have the same clock speed and share a lot of characteristics on PPU
	return 3200000000LL;
#else	
#if defined( _WIN32 )
	LARGE_INTEGER waitTime, startCount, curCount;
	CCycleCount start, end;

	// Take 1/32 of a second for the measurement.
	QueryPerformanceFrequency( &waitTime );
	int scale = 5;
	waitTime.QuadPart >>= scale;

	QueryPerformanceCounter( &startCount );
	start.Sample();
	do
	{
		QueryPerformanceCounter( &curCount );
	}
	while ( curCount.QuadPart - startCount.QuadPart < waitTime.QuadPart );
	end.Sample();

	return (end.m_Int64 - start.m_Int64) << scale;
#elif defined(POSIX)
	int64 freq =(int64)CalculateCPUFreq();
	if ( freq == 0 ) // couldn't calculate clock speed
	{
		Error( "Unable to determine CPU Frequency\n" );
	}
	return freq;
#else
	#error "Please implement Clock Speed function for this platform"
#endif
#endif
}


const CPUInformation& GetCPUInformation()
{
	static CPUInformation pi;

	// Has the structure already been initialized and filled out?
	if ( pi.m_Size == sizeof(pi) )
		return pi;

	// Redundant, but just in case the user somehow messes with the size.
	memset(&pi, 0x0, sizeof(pi));

	// Fill out the structure, and return it: 
	pi.m_Size = sizeof(pi);

	// Grab the processor frequency:
	pi.m_Speed = CalculateClockSpeed();
	
	// Get the logical and physical processor counts:
	pi.m_nLogicalProcessors = LogicalProcessorsPerPackage();

	bool bAuthenticAMD = ( 0 == V_tier0_stricmp( GetProcessorVendorId(), "AuthenticAMD" ) );
	bool bGenuineIntel = !bAuthenticAMD && ( 0 == V_tier0_stricmp( GetProcessorVendorId(), "GenuineIntel" ) );

#if defined( _X360 )
	pi.m_nPhysicalProcessors = 3;
	pi.m_nLogicalProcessors  = 6;
#elif defined( _PS3 )
	pi.m_nPhysicalProcessors = 1;
	pi.m_nLogicalProcessors  = 2;
#elif defined(_WIN32) && !defined( _X360 )
	SYSTEM_INFO si;
	ZeroMemory( &si, sizeof(si) );

	GetSystemInfo( &si );

	// Sergiy: fixing: si.dwNumberOfProcessors is the number of logical processors according to experiments on i7, P4 and a DirectX sample (Aug'09)
	//         this is contrary to MSDN documentation on GetSystemInfo()
	// 
	pi.m_nLogicalProcessors = si.dwNumberOfProcessors;

	if ( bAuthenticAMD )
	{
		// quick fix for AMD Phenom: it reports 3 logical cores and 4 physical cores;
		// no AMD CPUs by the end of 2009 have HT, so we'll override HT detection here
		pi.m_nPhysicalProcessors = pi.m_nLogicalProcessors;
	}
	else
	{
		CpuTopology topo;
		pi.m_nPhysicalProcessors = topo.NumberOfSystemCores();
	}

	// Make sure I always report at least one, when running WinXP with the /ONECPU switch, 
	// it likes to report 0 processors for some reason.
	if ( pi.m_nPhysicalProcessors == 0 && pi.m_nLogicalProcessors == 0 )
	{
		Assert( !"Sergiy: apparently I didn't fix some CPU detection code completely. Let me know and I'll do my best to fix it soon." );
		pi.m_nPhysicalProcessors = 1;
		pi.m_nLogicalProcessors  = 1;
	}
#elif defined(LINUX)
	pi.m_nLogicalProcessors = 0;
	pi.m_nPhysicalProcessors = 0;
	const int k_cMaxProcessors = 256;
	bool rgbProcessors[k_cMaxProcessors];
	memset( rgbProcessors, 0, sizeof( rgbProcessors ) );
	int cMaxCoreId = 0;

	FILE *fpCpuInfo = fopen( "/proc/cpuinfo", "r" );
	if ( fpCpuInfo )
	{
		char rgchLine[256];
		while ( fgets( rgchLine, sizeof( rgchLine ), fpCpuInfo ) )
		{
			if ( !strncasecmp( rgchLine, "processor", strlen( "processor" ) ) )
			{
				pi.m_nLogicalProcessors++;
			}
			if ( !strncasecmp( rgchLine, "core id", strlen( "core id" ) ) )
			{
				char *pchValue = strchr( rgchLine, ':' );
				cMaxCoreId = MAX( cMaxCoreId, atoi( pchValue + 1 ) );
			}
			if ( !strncasecmp( rgchLine, "physical id", strlen( "physical id" ) ) )
			{
				// it seems (based on survey data) that we can see
				// processor N (N > 0) when it's the only processor in
				// the system.  so keep track of each processor
				char *pchValue = strchr( rgchLine, ':' );
				int cPhysicalId = atoi( pchValue + 1 );
				if ( cPhysicalId < k_cMaxProcessors )
					rgbProcessors[cPhysicalId] = true;
			}
			/* this code will tell us how many physical chips are in the machine, but we want
			   core count, so for the moment, each processor counts as both logical and physical.
			if ( !strncasecmp( rgchLine, "physical id ", strlen( "physical id " ) ) )
			{
				char *pchValue = strchr( rgchLine, ':' );
				pi.m_nPhysicalProcessors = MAX( pi.m_nPhysicalProcessors, atol( pchValue ) );
			}
			*/
		}
		fclose( fpCpuInfo );
		for ( int i = 0; i < k_cMaxProcessors; i++ )
			if ( rgbProcessors[i] )
				pi.m_nPhysicalProcessors++;
		pi.m_nPhysicalProcessors *= ( cMaxCoreId + 1 );
	}
	else
	{
		pi.m_nLogicalProcessors = 1;
		pi.m_nPhysicalProcessors = 1;
		Assert( !"couldn't read cpu information from /proc/cpuinfo" );
	}

#elif defined(OSX)

	int num_phys_cpu = 1, num_log_cpu = 1;
	size_t len = sizeof(num_phys_cpu);
	sysctlbyname( "hw.physicalcpu", &num_phys_cpu, &len, NULL, 0 );
	sysctlbyname( "hw.logicalcpu", &num_log_cpu, &len, NULL, 0 );
	pi.m_nPhysicalProcessors = num_phys_cpu;
	pi.m_nLogicalProcessors  = num_log_cpu;

#endif

	CpuIdResult_t cpuid0 = cpuid( 0 );
	if ( cpuid0.eax >= 1 )
	{
		CpuIdResult_t cpuid1 = cpuid( 1 );
		uint bFPU = cpuid1.edx & 1; // this should always be on on anything we support
		// Determine Processor Features:
		pi.m_bRDTSC = ( cpuid1.edx >> 4 ) & 1;
		pi.m_bCMOV = ( cpuid1.edx >> 15 ) & 1;
		pi.m_bFCMOV = ( pi.m_bCMOV && bFPU ) ? 1 : 0;
		pi.m_bMMX = ( cpuid1.edx >> 23 ) & 1;
		pi.m_bSSE = ( cpuid1.edx >> 25 ) & 1;
		pi.m_bSSE2 = ( cpuid1.edx >> 26 ) & 1;
		pi.m_bSSE3 = cpuid1.ecx & 1;
		pi.m_bSSSE3 = ( cpuid1.ecx >> 9 ) & 1;;
		pi.m_bSSE4a = CheckSSE4aTechnology();
		pi.m_bSSE41 = ( cpuid1.ecx >> 19 ) & 1;
		pi.m_bSSE42 = ( cpuid1.ecx >> 20 ) & 1;
		pi.m_b3DNow = Check3DNowTechnology();
		pi.m_bAVX	= ( cpuid1.ecx >> 28 ) & 1;
		pi.m_szProcessorID = ( tchar* )GetProcessorVendorId();
		pi.m_szProcessorBrand = ( tchar* )GetProcessorBrand();
		pi.m_bHT = ( pi.m_nPhysicalProcessors < pi.m_nLogicalProcessors ); //HTSupported();

		pi.m_nModel			= cpuid1.eax; // full CPU model info
		pi.m_nFeatures[ 0 ] = cpuid1.edx; // x87+ features
		pi.m_nFeatures[ 1 ] = cpuid1.ecx; // sse3+ features
		pi.m_nFeatures[ 2 ] = cpuid1.ebx; // some additional features
	}

	return pi;
}

