project(android-external-icu4c-icuuc)

include_directories(. ../i18n)

add_definitions(-D_REENTRANT)
add_definitions(-DU_COMMON_IMPLEMENTATION)
# bionic doesn't have <langinfo.h>.
add_definitions(-DU_HAVE_NL_LANGINFO_CODESET=0)
# bionic has timezone instead of __timezone.
add_definitions(-DU_TIMEZONE=timezone)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-switch -Wno-enum-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-parentheses -Wno-unused-function -Wno-deprecated-declarations")

set(SRC
	cmemory.c cstring.c cwchar.c icudataver.c icuplug.c locmap.c 
	propsvec.c uarrsort.c ubidi.c ubidiln.c ubidiwrt.c ubidi_props.c 
	ucat.c uchar.c ucln_cmn.c ucmndata.c ucnv.c ucnvdisp.c ucnvhz.c 
	ucnvisci.c ucnvlat1.c ucnvmbcs.c ucnvscsu.c ucnv_cb.c 
	ucnv_cnv.c ucnv_ct.c ucnv_err.c ucnv_lmb.c ucnv_set.c 
	ucnv_u16.c ucnv_u32.c ucnv_u7.c ucnv_u8.c udatamem.c 
	udataswp.c uenum.c uhash.c uinit.c uinvchar.c ulist.c 
	uloc_tag.c umapfile.c umath.c unorm_it.c uresdata.c 
	ures_cnv.c uscript.c usc_impl.c ustrfmt.c ustr_cnv.c 
	utf_impl.c utrace.c utypes.c wintz.c appendable.cpp bmpset.cpp 
	brkeng.cpp brkiter.cpp bytestream.cpp bytestrie.cpp bytestriebuilder.cpp 
	bytestrieiterator.cpp caniter.cpp chariter.cpp charstr.cpp 
	dictbe.cpp dictionarydata.cpp dtintrv.cpp errorcode.cpp 
	filterednormalizer2.cpp listformatter.cpp locavailable.cpp 
	locbased.cpp locdispnames.cpp locid.cpp loclikely.cpp locresdata.cpp 
	locutil.cpp messagepattern.cpp mutex.cpp normalizer2.cpp 
	normalizer2impl.cpp normlzr.cpp parsepos.cpp patternprops.cpp 
	propname.cpp punycode.cpp putil.cpp rbbi.cpp rbbidata.cpp 
	rbbinode.cpp rbbirb.cpp rbbiscan.cpp rbbisetb.cpp rbbistbl.cpp 
	rbbitblb.cpp resbund.cpp resbund_cnv.cpp ruleiter.cpp schriter.cpp 
	serv.cpp servlk.cpp servlkf.cpp servls.cpp servnotf.cpp servrbf.cpp 
	servslkf.cpp stringpiece.cpp stringtriebuilder.cpp ubrk.cpp ucase.cpp 
	ucasemap.cpp ucasemap_titlecase_brkiter.cpp ucharstrie.cpp 
	ucharstriebuilder.cpp ucharstrieiterator.cpp uchriter.cpp ucnv2022.cpp 
	ucnvbocu.cpp ucnvsel.cpp ucnv_bld.cpp ucnv_ext.cpp ucnv_io.cpp 
	ucol_swp.cpp udata.cpp uhash_us.cpp uidna.cpp uiter.cpp uloc.cpp 
	umutex.cpp unames.cpp unifilt.cpp unifunct.cpp uniset.cpp unisetspan.cpp 
	uniset_closure.cpp uniset_props.cpp unistr.cpp unistr_case.cpp 
	unistr_case_locale.cpp unistr_cnv.cpp unistr_props.cpp unistr_titlecase_brkiter.cpp 
	unorm.cpp unormcmp.cpp uobject.cpp uprops.cpp uresbund.cpp uscript_props.cpp 
	uset.cpp usetiter.cpp uset_props.cpp ushape.cpp usprep.cpp ustack.cpp 
	ustrcase.cpp ustrcase_locale.cpp ustrenum.cpp ustring.cpp ustrtrns.cpp 
	ustr_titlecase_brkiter.cpp ustr_wcs.cpp utext.cpp util.cpp util_props.cpp 
	utrie.cpp utrie2.cpp utrie2_builder.cpp uts46.cpp uvector.cpp uvectr32.cpp uvectr64.cpp
  ../stubdata/stubdata.c
)

add_library(android-external-icu4c-icuuc OBJECT ${SRC})
set(EXTERNAL_ICU4C_COMMON_OBJECTS $<TARGET_OBJECTS:android-external-icu4c-icuuc> PARENT_SCOPE)

