#include "typedef.h"
#define TYPE_DATA(X) _Generic((X),		\
			      _Bool:4,		\
			      char:5,		\
			      schar:8,		\
			      short:11,		\
			      us__t:14,		\
			      int:17,		\
			      ui__t:20,		\
			      long:23,		\
			      ulg__t:26,	\
			      llg__t:29,	\
			      ullg__t:32,	\
			      float:35,		\
			      double:38,	\
			      ld__t:41,		\
			      _Cf__t:44,	\
			      _Cd__t:47,	\
			      _Cld__t:50,	\
			      /*FILEp__t:53,*/	\
			      /*list__t:56,*/	\
			      default: -1	\
			      )
  

#define TYPE_PTR(X) _Generic((X),		\
			     void*:59,		\
			     char*:62,		\
			     pschar:65,		\
			     short*:68,		\
			     usp__t:71,		\
			     int*:74,		\
			     uip__t:77,		\
			     long*:80,		\
			     ulgp__t:83,	\
			     llgp__t:86,	\
			     ullgp__t:89,	\
			     float*:92,		\
			     double*:95,	\
			     ldp__t:98,		\
			     _Cfp__t:101,	\
			     _Cdp__t:104,	\
			     _Cldp__t:107,	\
			     /*pFILEp__t:110,*/	\
			     listp__t:113,	\
			     default: -1	\
			     )


#define TYPE_DPTR(X) _Generic((X),		\
			      void **:116,	\
			      char **:119,	\
			      sgxchar:122,	\
			      short **:125,	\
			      uspp__t:128,	\
			      int **:131,	\
			      uipp__t:134,	\
			      long **:137,	\
			      ulgpp__t:140,	\
			      llgpp__t:143,	\
			      ullgpp__t:146,	\
			      float **:149,	\
			      double **:152,	\
			      ldpp__t:155,	\
			      _Cfpp__t:158,	\
			      _Cdpp__t:161,	\
			      _Cldpp__t:164,	\
			      listpp__t:167,	\
			      default: -1	\
			      )
#if _EXTEND_TYPE_FUNC_  
#define TYPE_FUNCTION_PTR_1(X) _Generic((X),		\
					vdF__t:2,	\
					vdF2__t:3,	\
					chF__t:6,	\
					chF2__t:7,	\
					sgF__t:9,	\
					sgF2__t:10,	\
					shF__t:12,	\
					shF2__t:13,	\
					usF__t:15,	\
					usF2__t:16,	\
					iF__t:18,	\
					iF2__t:19,	\
					uiF__t:21,	\
					uiF2__t:22,	\
					lgF__t:24,	\
					lgF2__t:25,	\
					ulgF__t:27,	\
					ulgF2__t:28,	\
					llgF__t:30,	\
					llgF2__t:31,	\
					ullgF__t:33,	\
					ullgF2__t:34,	\
					fF__t:36,	\
					fF2__t:37,	\
					dF__t:39,	\
					dF2__t:40,	\
					ldF__t:42,	\
					ldF2__t:43,	\
					_CfF__t:45,	\
					_CfF2__t:46,	\
					_CdF__t:48,	\
					_CdF2__t:49,	\
					_CldF__t:51,	\
					_CldF2__t:52,	\
					/*FILEpF__t:54,*/	\
					/*FILE2F__t:55,*/	\
					listF__t:57,	\
					listF2__t:58,	\
					default: -1	\
					)


#define TYPE_FUNCTION_DPTR(X)_Generic((X),\
				      vdpF__t:60,	\
				      vdpF2__t:61,	\
				      chpF__t:63,	\
				      chpF2__t:64,	\
				      sgpF__t:66,	\
				      sgpF2__t:67,	\
				      shpF__t:69,	\
				      shpF2__t:70,	\
				      uspF__t:72,	\
				      uspF2__t:73,	\
				      ipF__t:75,	\
				      ipF2__t:76,	\
				      uipF__t:78,	\
				      uipF2__t:79,	\
				      lgpF__t:81,	\
				      lgpF2__t:82,	\
				      ulgpF__t:84,	\
				      ulgpF2__t:85,	\
				      llgpF__t:87,	\
				      llgpF2__t:88,	\
				      ullgpF__t:90,	\
				      ullgpF2__t:91,	\
				      fpF__t:93,	\
				      fpF2__t:94,	\
				      dpF__t:96,	\
				      dpF2__t:97,	\
				      ldpF__t:99,	\
				      ldpF2__t:100,	\
				      _CfpF__t:102,	\
				      _CfpF2__t:103,	\
				      _CdpF__t:105,	\
				      _CdpF2__t:106,	\
				      _CldpF__t:108,	\
				      _CldpF2__t:109,	\
				      /*pFILEppF__t:111*/,	\
				      /*pFILE2F__t:112,*/	\
				      listpF__t:114,	\
				      listpF2__t:115,	\
				      default: -1	\
				      )


#define TYPE_FUNCTION_DDPTR(X)_Generic((X),	\
				       vdx__t:117,	\
				       vdx2__t:118,	\
				       chx__t:120,	\
				       chx2__t:121,	\
				       sgx__t:123,	\
				       sgx2__t:124,	\
				       shx__t:126,	\
				       shx2__t:127,	\
				       usx__t:129,	\
				       usx2__t:130,	\
				       ix__t:132,	\
				       ix2__t:133,	\
				       uix__t:135,	\
				       uix2__t:136,	\
				       lgx__t:138,	\
				       lgx2__t:139,	\
				       ulgx__t:141,	\
				       ulgx2__t:142,	\
				       llgx__t:144,	\
				       llgx2__t:145,	\
				       ullgx__t:147,	\
				       ullgx2__t:148,	\
				       fx__t:150,	\
				       fx2__t:151,	\
				       dx__t:153,	\
				       dx2__t:154,	\
				       ldx__t:156,	\
				       ldx2__t:157,	\
				       _Cfx__t:159,	\
				       _Cfx2__t:160,	\
				       _Cdx__t:162,	\
				       _Cdx2__t:163,	\
				       _Cldx__t:165,	\
				       _Cldx2__t:166,	\
				       listx__t:168,	\
				       listx2__t:169,	\
				       default: -1	\
				       )
#endif //_EXTEND_TYPE_FUNC_
