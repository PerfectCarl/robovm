project(android-external-icu4c-icui18n)

include_directories(. ../common)

add_definitions(-D_REENTRANT)
add_definitions(-DU_I18N_IMPLEMENTATION)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-parentheses -Wno-unused-function -Wno-deprecated-declarations")

set(SRC
	alphaindex.cpp anytrans.cpp astro.cpp basictz.cpp bocsu.cpp 
	brktrans.cpp buddhcal.cpp calendar.cpp casetrn.cpp cecal.cpp 
	chnsecal.cpp choicfmt.cpp coleitr.cpp coll.cpp compactdecimalformat.cpp 
	coptccal.cpp cpdtrans.cpp csdetect.cpp csmatch.cpp 
	csr2022.cpp csrecog.cpp csrmbcs.cpp csrsbcs.cpp csrucode.cpp 
	csrutf8.cpp curramt.cpp currfmt.cpp currpinf.cpp currunit.cpp 
	dangical.cpp datefmt.cpp dcfmtsym.cpp decfmtst.cpp decimfmt.cpp 
	digitlst.cpp dtfmtsym.cpp dtitvfmt.cpp dtitvinf.cpp dtptngen.cpp 
	dtrule.cpp esctrn.cpp ethpccal.cpp fmtable.cpp fmtable_cnv.cpp 
	format.cpp fphdlimp.cpp fpositer.cpp funcrepl.cpp gender.cpp 
	gregocal.cpp gregoimp.cpp hebrwcal.cpp identifier_info.cpp 
	indiancal.cpp inputext.cpp islamcal.cpp japancal.cpp locdspnm.cpp 
	measfmt.cpp measure.cpp msgfmt.cpp name2uni.cpp nfrs.cpp 
	nfrule.cpp nfsubs.cpp nortrans.cpp nultrans.cpp numfmt.cpp 
	numsys.cpp olsontz.cpp persncal.cpp plurfmt.cpp plurrule.cpp 
	quant.cpp rbnf.cpp rbt.cpp rbtz.cpp rbt_data.cpp rbt_pars.cpp 
	rbt_rule.cpp rbt_set.cpp regexcmp.cpp regeximp.cpp regexst.cpp 
	regextxt.cpp region.cpp reldtfmt.cpp rematch.cpp remtrans.cpp 
	repattrn.cpp scriptset.cpp search.cpp selfmt.cpp simpletz.cpp 
	smpdtfmt.cpp smpdtfst.cpp sortkey.cpp strmatch.cpp strrepl.cpp 
	stsearch.cpp taiwncal.cpp tblcoll.cpp timezone.cpp titletrn.cpp 
	tmunit.cpp tmutamt.cpp tmutfmt.cpp tolowtrn.cpp toupptrn.cpp 
	translit.cpp transreg.cpp tridpars.cpp tzfmt.cpp tzgnames.cpp 
	tznames.cpp tznames_impl.cpp tzrule.cpp tztrans.cpp ucal.cpp 
	ucol.cpp ucoleitr.cpp ucol_bld.cpp ucol_cnt.cpp ucol_elm.cpp ucol_res.cpp 
	ucol_sit.cpp ucol_tok.cpp ucol_wgt.cpp ucsdet.cpp ucurr.cpp udat.cpp 
	udateintervalformat.cpp udatpg.cpp umsg.cpp unesctrn.cpp uni2name.cpp 
	unum.cpp upluralrules.cpp uregex.cpp uregexc.cpp usearch.cpp uspoof.cpp 
	uspoof_build.cpp uspoof_conf.cpp uspoof_impl.cpp uspoof_wsconf.cpp 
	utrans.cpp vtzone.cpp vzone.cpp windtfmt.cpp winnmfmt.cpp wintzimpl.cpp 
	zonemeta.cpp zrule.cpp ztrans.cpp decContext.c decNumber.c ucln_in.c 
	ulocdata.c utmscale.c
)

add_library(android-external-icu4c-icui18n OBJECT ${SRC})
set(EXTERNAL_ICU4C_I18N_OBJECTS $<TARGET_OBJECTS:android-external-icu4c-icui18n> PARENT_SCOPE)

