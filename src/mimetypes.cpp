/*************************
 *         htt++         *
 *************************
 *      MIME Module      *
 *      Header File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#include "mimetypes.hpp"

namespace httpp
{
	sprawl::multiaccess::multiaccess_map<MimeMap> MimeTypes(&MimeMap::getExtension, &MimeMap::getMimeType);

	boost::mutex MimeTypeMutex;
	bool MimeTypesPopulated;
	
	//MimeTypes taken from Apache mime types
	//http://svn.apache.org/viewvc/httpd/httpd/branches/2.2.x/docs/conf/mime.types?revision=1301896
	//Most revisions listed here: http://svn.apache.org/viewvc/httpd/httpd/branches/2.2.x/docs/conf/mime.types?view=log
	//Current revision used is 1301896, updated March 17 2012
	//Doing this as one long function makes compilation time a bit ridiculous, so they're split up alphabetically.
	namespace
	{
		void PopulateTypes_Num()
		{
			MimeTypes.push(MimeMap("123", "application/vnd.lotus-1-2-3"));
			MimeTypes.push(MimeMap("3dml", "text/vnd.in3d.3dml"));
			MimeTypes.push(MimeMap("3ds", "image/x-3ds"));
			MimeTypes.push(MimeMap("3g2", "video/3gpp2"));
			MimeTypes.push(MimeMap("3gp", "video/3gpp"));
			MimeTypes.push(MimeMap("7z", "application/x-7z-compressed"));
		}
		
		void PopulateTypes_A()
		{
			MimeTypes.push(MimeMap("aab", "application/x-authorware-bin"));
			MimeTypes.push(MimeMap("aac", "audio/x-aac"));
			MimeTypes.push(MimeMap("aam", "application/x-authorware-map"));
			MimeTypes.push(MimeMap("aas", "application/x-authorware-seg"));
			MimeTypes.push(MimeMap("abw", "application/x-abiword"));
			MimeTypes.push(MimeMap("ac", "application/pkix-attr-cert"));
			MimeTypes.push(MimeMap("acc", "application/vnd.americandynamics.acc"));
			MimeTypes.push(MimeMap("ace", "application/x-ace-compressed"));
			MimeTypes.push(MimeMap("acu", "application/vnd.acucobol"));
			MimeTypes.push(MimeMap("acutc", "application/vnd.acucorp"));
			MimeTypes.push(MimeMap("adp", "audio/adpcm"));
			MimeTypes.push(MimeMap("aep", "application/vnd.audiograph"));
			MimeTypes.push(MimeMap("afm", "application/x-font-type1"));
			MimeTypes.push(MimeMap("afp", "application/vnd.ibm.modcap"));
			MimeTypes.push(MimeMap("ahead", "application/vnd.ahead.space"));
			MimeTypes.push(MimeMap("ai", "application/postscript"));
			MimeTypes.push(MimeMap("aif", "audio/x-aiff"));
			MimeTypes.push(MimeMap("aifc", "audio/x-aiff"));
			MimeTypes.push(MimeMap("aiff", "audio/x-aiff"));
			MimeTypes.push(MimeMap("air", "application/vnd.adobe.air-application-installer-package+zip"));
			MimeTypes.push(MimeMap("ait", "application/vnd.dvb.ait"));
			MimeTypes.push(MimeMap("ami", "application/vnd.amiga.ami"));
			MimeTypes.push(MimeMap("apk", "application/vnd.android.package-archive"));
			MimeTypes.push(MimeMap("appcache", "text/cache-manifest"));
			MimeTypes.push(MimeMap("application", "application/x-ms-application"));
			MimeTypes.push(MimeMap("apr", "application/vnd.lotus-approach"));
			MimeTypes.push(MimeMap("arc", "application/x-freearc"));
			MimeTypes.push(MimeMap("asc", "application/pgp-signature"));
			MimeTypes.push(MimeMap("asf", "video/x-ms-asf"));
			MimeTypes.push(MimeMap("asm", "text/x-asm"));
			MimeTypes.push(MimeMap("aso", "application/vnd.accpac.simply.aso"));
			MimeTypes.push(MimeMap("asx", "video/x-ms-asf"));
			MimeTypes.push(MimeMap("atc", "application/vnd.acucorp"));
			MimeTypes.push(MimeMap("atom", "application/atom+xml"));
			MimeTypes.push(MimeMap("atomcat", "application/atomcat+xml"));
			MimeTypes.push(MimeMap("atomsvc", "application/atomsvc+xml"));
			MimeTypes.push(MimeMap("atx", "application/vnd.antix.game-component"));
			MimeTypes.push(MimeMap("au", "audio/basic"));
			MimeTypes.push(MimeMap("avi", "video/x-msvideo"));
			MimeTypes.push(MimeMap("aw", "application/applixware"));
			MimeTypes.push(MimeMap("azf", "application/vnd.airzip.filesecure.azf"));
			MimeTypes.push(MimeMap("azs", "application/vnd.airzip.filesecure.azs"));
			MimeTypes.push(MimeMap("azw", "application/vnd.amazon.ebook"));
		}
		
		void PopulateTypes_B()
		{
			MimeTypes.push(MimeMap("bat", "application/x-msdownload"));
			MimeTypes.push(MimeMap("bcpio", "application/x-bcpio"));
			MimeTypes.push(MimeMap("bdf", "application/x-font-bdf"));
			MimeTypes.push(MimeMap("bdm", "application/vnd.syncml.dm+wbxml"));
			MimeTypes.push(MimeMap("bed", "application/vnd.realvnc.bed"));
			MimeTypes.push(MimeMap("bh2", "application/vnd.fujitsu.oasysprs"));
			MimeTypes.push(MimeMap("bin", "application/octet-stream"));
			MimeTypes.push(MimeMap("blb", "application/x-blorb"));
			MimeTypes.push(MimeMap("blorb", "application/x-blorb"));
			MimeTypes.push(MimeMap("bmi", "application/vnd.bmi"));
			MimeTypes.push(MimeMap("bmp", "image/bmp"));
			MimeTypes.push(MimeMap("book", "application/vnd.framemaker"));
			MimeTypes.push(MimeMap("box", "application/vnd.previewsystems.box"));
			MimeTypes.push(MimeMap("boz", "application/x-bzip2"));
			MimeTypes.push(MimeMap("bpk", "application/octet-stream"));
			MimeTypes.push(MimeMap("btif", "image/prs.btif"));
			MimeTypes.push(MimeMap("bz", "application/x-bzip"));
			MimeTypes.push(MimeMap("bz2", "application/x-bzip2"));
		}
		
		void PopulateTypes_C()
		{
			MimeTypes.push(MimeMap("c", "text/x-c"));
			MimeTypes.push(MimeMap("c11amc", "application/vnd.cluetrust.cartomobile-config"));
			MimeTypes.push(MimeMap("c11amz", "application/vnd.cluetrust.cartomobile-config-pkg"));
			MimeTypes.push(MimeMap("c4d", "application/vnd.clonk.c4group"));
			MimeTypes.push(MimeMap("c4f", "application/vnd.clonk.c4group"));
			MimeTypes.push(MimeMap("c4g", "application/vnd.clonk.c4group"));
			MimeTypes.push(MimeMap("c4p", "application/vnd.clonk.c4group"));
			MimeTypes.push(MimeMap("c4u", "application/vnd.clonk.c4group"));
			MimeTypes.push(MimeMap("cab", "application/vnd.ms-cab-compressed"));
			MimeTypes.push(MimeMap("caf", "audio/x-caf"));
			MimeTypes.push(MimeMap("cap", "application/vnd.tcpdump.pcap"));
			MimeTypes.push(MimeMap("car", "application/vnd.curl.car"));
			MimeTypes.push(MimeMap("cat", "application/vnd.ms-pki.seccat"));
			MimeTypes.push(MimeMap("cb7", "application/x-cbr"));
			MimeTypes.push(MimeMap("cba", "application/x-cbr"));
			MimeTypes.push(MimeMap("cbr", "application/x-cbr"));
			MimeTypes.push(MimeMap("cbt", "application/x-cbr"));
			MimeTypes.push(MimeMap("cbz", "application/x-cbr"));
			MimeTypes.push(MimeMap("cc", "text/x-c"));
			MimeTypes.push(MimeMap("cct", "application/x-director"));
			MimeTypes.push(MimeMap("ccxml", "application/ccxml+xml"));
			MimeTypes.push(MimeMap("cdbcmsg", "application/vnd.contact.cmsg"));
			MimeTypes.push(MimeMap("cdf", "application/x-netcdf"));
			MimeTypes.push(MimeMap("cdkey", "application/vnd.mediastation.cdkey"));
			MimeTypes.push(MimeMap("cdmia", "application/cdmi-capability"));
			MimeTypes.push(MimeMap("cdmic", "application/cdmi-container"));
			MimeTypes.push(MimeMap("cdmid", "application/cdmi-domain"));
			MimeTypes.push(MimeMap("cdmio", "application/cdmi-object"));
			MimeTypes.push(MimeMap("cdmiq", "application/cdmi-queue"));
			MimeTypes.push(MimeMap("cdx", "chemical/x-cdx"));
			MimeTypes.push(MimeMap("cdxml", "application/vnd.chemdraw+xml"));
			MimeTypes.push(MimeMap("cdy", "application/vnd.cinderella"));
			MimeTypes.push(MimeMap("cer", "application/pkix-cert"));
			MimeTypes.push(MimeMap("cfs", "application/x-cfs-compressed"));
			MimeTypes.push(MimeMap("cgm", "image/cgm"));
			MimeTypes.push(MimeMap("chat", "application/x-chat"));
			MimeTypes.push(MimeMap("chm", "application/vnd.ms-htmlhelp"));
			MimeTypes.push(MimeMap("chrt", "application/vnd.kde.kchart"));
			MimeTypes.push(MimeMap("cif", "chemical/x-cif"));
			MimeTypes.push(MimeMap("cii", "application/vnd.anser-web-certificate-issue-initiation"));
			MimeTypes.push(MimeMap("cil", "application/vnd.ms-artgalry"));
			MimeTypes.push(MimeMap("cla", "application/vnd.claymore"));
			MimeTypes.push(MimeMap("class", "application/java-vm"));
			MimeTypes.push(MimeMap("clkk", "application/vnd.crick.clicker.keyboard"));
			MimeTypes.push(MimeMap("clkp", "application/vnd.crick.clicker.palette"));
			MimeTypes.push(MimeMap("clkt", "application/vnd.crick.clicker.template"));
			MimeTypes.push(MimeMap("clkw", "application/vnd.crick.clicker.wordbank"));
			MimeTypes.push(MimeMap("clkx", "application/vnd.crick.clicker"));
			MimeTypes.push(MimeMap("clp", "application/x-msclip"));
			MimeTypes.push(MimeMap("cmc", "application/vnd.cosmocaller"));
			MimeTypes.push(MimeMap("cmdf", "chemical/x-cmdf"));
			MimeTypes.push(MimeMap("cml", "chemical/x-cml"));
			MimeTypes.push(MimeMap("cmp", "application/vnd.yellowriver-custom-menu"));
			MimeTypes.push(MimeMap("cmx", "image/x-cmx"));
			MimeTypes.push(MimeMap("cod", "application/vnd.rim.cod"));
			MimeTypes.push(MimeMap("com", "application/x-msdownload"));
			MimeTypes.push(MimeMap("conf", "text/plain"));
			MimeTypes.push(MimeMap("cpio", "application/x-cpio"));
			MimeTypes.push(MimeMap("cpp", "text/x-c"));
			MimeTypes.push(MimeMap("cpt", "application/mac-compactpro"));
			MimeTypes.push(MimeMap("crd", "application/x-mscardfile"));
			MimeTypes.push(MimeMap("crl", "application/pkix-crl"));
			MimeTypes.push(MimeMap("crt", "application/x-x509-ca-cert"));
			MimeTypes.push(MimeMap("cryptonote", "application/vnd.rig.cryptonote"));
			MimeTypes.push(MimeMap("csh", "application/x-csh"));
			MimeTypes.push(MimeMap("csml", "chemical/x-csml"));
			MimeTypes.push(MimeMap("csp", "application/vnd.commonspace"));
			MimeTypes.push(MimeMap("css", "text/css"));
			MimeTypes.push(MimeMap("cst", "application/x-director"));
			MimeTypes.push(MimeMap("csv", "text/csv"));
			MimeTypes.push(MimeMap("cu", "application/cu-seeme"));
			MimeTypes.push(MimeMap("curl", "text/vnd.curl"));
			MimeTypes.push(MimeMap("cww", "application/prs.cww"));
			MimeTypes.push(MimeMap("cxt", "application/x-director"));
			MimeTypes.push(MimeMap("cxx", "text/x-c"));
		}
		
		void PopulateTypes_D()
		{
			MimeTypes.push(MimeMap("dae", "model/vnd.collada+xml"));
			MimeTypes.push(MimeMap("daf", "application/vnd.mobius.daf"));
			MimeTypes.push(MimeMap("dart", "application/vnd.dart"));
			MimeTypes.push(MimeMap("dataless", "application/vnd.fdsn.seed"));
			MimeTypes.push(MimeMap("davmount", "application/davmount+xml"));
			MimeTypes.push(MimeMap("dbk", "application/docbook+xml"));
			MimeTypes.push(MimeMap("dcr", "application/x-director"));
			MimeTypes.push(MimeMap("dcurl", "text/vnd.curl.dcurl"));
			MimeTypes.push(MimeMap("dd2", "application/vnd.oma.dd2+xml"));
			MimeTypes.push(MimeMap("ddd", "application/vnd.fujixerox.ddd"));
			MimeTypes.push(MimeMap("deb", "application/x-debian-package"));
			MimeTypes.push(MimeMap("def", "text/plain"));
			MimeTypes.push(MimeMap("deploy", "application/octet-stream"));
			MimeTypes.push(MimeMap("der", "application/x-x509-ca-cert"));
			MimeTypes.push(MimeMap("dfac", "application/vnd.dreamfactory"));
			MimeTypes.push(MimeMap("dgc", "application/x-dgc-compressed"));
			MimeTypes.push(MimeMap("dic", "text/x-c"));
			MimeTypes.push(MimeMap("dir", "application/x-director"));
			MimeTypes.push(MimeMap("dis", "application/vnd.mobius.dis"));
			MimeTypes.push(MimeMap("dist", "application/octet-stream"));
			MimeTypes.push(MimeMap("distz", "application/octet-stream"));
			MimeTypes.push(MimeMap("djv", "image/vnd.djvu"));
			MimeTypes.push(MimeMap("djvu", "image/vnd.djvu"));
			MimeTypes.push(MimeMap("dll", "application/x-msdownload"));
			MimeTypes.push(MimeMap("dmg", "application/x-apple-diskimage"));
			MimeTypes.push(MimeMap("dmp", "application/vnd.tcpdump.pcap"));
			MimeTypes.push(MimeMap("dms", "application/octet-stream"));
			MimeTypes.push(MimeMap("dna", "application/vnd.dna"));
			MimeTypes.push(MimeMap("doc", "application/msword"));
			MimeTypes.push(MimeMap("docm", "application/vnd.ms-word.document.macroenabled.12"));
			MimeTypes.push(MimeMap("docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"));
			MimeTypes.push(MimeMap("dot", "application/msword"));
			MimeTypes.push(MimeMap("dotm", "application/vnd.ms-word.template.macroenabled.12"));
			MimeTypes.push(MimeMap("dotx", "application/vnd.openxmlformats-officedocument.wordprocessingml.template"));
			MimeTypes.push(MimeMap("dp", "application/vnd.osgi.dp"));
			MimeTypes.push(MimeMap("dpg", "application/vnd.dpgraph"));
			MimeTypes.push(MimeMap("dra", "audio/vnd.dra"));
			MimeTypes.push(MimeMap("dsc", "text/prs.lines.tag"));
			MimeTypes.push(MimeMap("dssc", "application/dssc+der"));
			MimeTypes.push(MimeMap("dtb", "application/x-dtbook+xml"));
			MimeTypes.push(MimeMap("dtd", "application/xml-dtd"));
			MimeTypes.push(MimeMap("dts", "audio/vnd.dts"));
			MimeTypes.push(MimeMap("dtshd", "audio/vnd.dts.hd"));
			MimeTypes.push(MimeMap("dump", "application/octet-stream"));
			MimeTypes.push(MimeMap("dvb", "video/vnd.dvb.file"));
			MimeTypes.push(MimeMap("dvi", "application/x-dvi"));
			MimeTypes.push(MimeMap("dwf", "model/vnd.dwf"));
			MimeTypes.push(MimeMap("dwg", "image/vnd.dwg"));
			MimeTypes.push(MimeMap("dxf", "image/vnd.dxf"));
			MimeTypes.push(MimeMap("dxp", "application/vnd.spotfire.dxp"));
			MimeTypes.push(MimeMap("dxr", "application/x-director"));
		}
		
		void PopulateTypes_E()
		{
			MimeTypes.push(MimeMap("ecelp4800", "audio/vnd.nuera.ecelp4800"));
			MimeTypes.push(MimeMap("ecelp7470", "audio/vnd.nuera.ecelp7470"));
			MimeTypes.push(MimeMap("ecelp9600", "audio/vnd.nuera.ecelp9600"));
			MimeTypes.push(MimeMap("ecma", "application/ecmascript"));
			MimeTypes.push(MimeMap("edm", "application/vnd.novadigm.edm"));
			MimeTypes.push(MimeMap("edx", "application/vnd.novadigm.edx"));
			MimeTypes.push(MimeMap("efif", "application/vnd.picsel"));
			MimeTypes.push(MimeMap("ei6", "application/vnd.pg.osasli"));
			MimeTypes.push(MimeMap("elc", "application/octet-stream"));
			MimeTypes.push(MimeMap("emf", "application/x-msmetafile"));
			MimeTypes.push(MimeMap("eml", "message/rfc822"));
			MimeTypes.push(MimeMap("emma", "application/emma+xml"));
			MimeTypes.push(MimeMap("emz", "application/x-msmetafile"));
			MimeTypes.push(MimeMap("eol", "audio/vnd.digital-winds"));
			MimeTypes.push(MimeMap("eot", "application/vnd.ms-fontobject"));
			MimeTypes.push(MimeMap("eps", "application/postscript"));
			MimeTypes.push(MimeMap("epub", "application/epub+zip"));
			MimeTypes.push(MimeMap("es3", "application/vnd.eszigno3+xml"));
			MimeTypes.push(MimeMap("esa", "application/vnd.osgi.subsystem"));
			MimeTypes.push(MimeMap("esf", "application/vnd.epson.esf"));
			MimeTypes.push(MimeMap("et3", "application/vnd.eszigno3+xml"));
			MimeTypes.push(MimeMap("etx", "text/x-setext"));
			MimeTypes.push(MimeMap("eva", "application/x-eva"));
			MimeTypes.push(MimeMap("evy", "application/x-envoy"));
			MimeTypes.push(MimeMap("exe", "application/x-msdownload"));
			MimeTypes.push(MimeMap("exi", "application/exi"));
			MimeTypes.push(MimeMap("ext", "application/vnd.novadigm.ext"));
			MimeTypes.push(MimeMap("ez", "application/andrew-inset"));
			MimeTypes.push(MimeMap("ez2", "application/vnd.ezpix-album"));
			MimeTypes.push(MimeMap("ez3", "application/vnd.ezpix-package"));
		}
		
		void PopulateTypes_F()
		{
			MimeTypes.push(MimeMap("f", "text/x-fortran"));
			MimeTypes.push(MimeMap("f4v", "video/x-f4v"));
			MimeTypes.push(MimeMap("f77", "text/x-fortran"));
			MimeTypes.push(MimeMap("f90", "text/x-fortran"));
			MimeTypes.push(MimeMap("fbs", "image/vnd.fastbidsheet"));
			MimeTypes.push(MimeMap("fcdt", "application/vnd.adobe.formscentral.fcdt"));
			MimeTypes.push(MimeMap("fcs", "application/vnd.isac.fcs"));
			MimeTypes.push(MimeMap("fdf", "application/vnd.fdf"));
			MimeTypes.push(MimeMap("fe_launch", "application/vnd.denovo.fcselayout-link"));
			MimeTypes.push(MimeMap("fg5", "application/vnd.fujitsu.oasysgp"));
			MimeTypes.push(MimeMap("fgd", "application/x-director"));
			MimeTypes.push(MimeMap("fh", "image/x-freehand"));
			MimeTypes.push(MimeMap("fh4", "image/x-freehand"));
			MimeTypes.push(MimeMap("fh5", "image/x-freehand"));
			MimeTypes.push(MimeMap("fh7", "image/x-freehand"));
			MimeTypes.push(MimeMap("fhc", "image/x-freehand"));
			MimeTypes.push(MimeMap("fig", "application/x-xfig"));
			MimeTypes.push(MimeMap("flac", "audio/x-flac"));
			MimeTypes.push(MimeMap("fli", "video/x-fli"));
			MimeTypes.push(MimeMap("flo", "application/vnd.micrografx.flo"));
			MimeTypes.push(MimeMap("flv", "video/x-flv"));
			MimeTypes.push(MimeMap("flw", "application/vnd.kde.kivio"));
			MimeTypes.push(MimeMap("flx", "text/vnd.fmi.flexstor"));
			MimeTypes.push(MimeMap("fly", "text/vnd.fly"));
			MimeTypes.push(MimeMap("fm", "application/vnd.framemaker"));
			MimeTypes.push(MimeMap("fnc", "application/vnd.frogans.fnc"));
			MimeTypes.push(MimeMap("for", "text/x-fortran"));
			MimeTypes.push(MimeMap("fpx", "image/vnd.fpx"));
			MimeTypes.push(MimeMap("frame", "application/vnd.framemaker"));
			MimeTypes.push(MimeMap("fsc", "application/vnd.fsc.weblaunch"));
			MimeTypes.push(MimeMap("fst", "image/vnd.fst"));
			MimeTypes.push(MimeMap("ftc", "application/vnd.fluxtime.clip"));
			MimeTypes.push(MimeMap("fti", "application/vnd.anser-web-funds-transfer-initiation"));
			MimeTypes.push(MimeMap("fvt", "video/vnd.fvt"));
			MimeTypes.push(MimeMap("fxp", "application/vnd.adobe.fxp"));
			MimeTypes.push(MimeMap("fxpl", "application/vnd.adobe.fxp"));
			MimeTypes.push(MimeMap("fzs", "application/vnd.fuzzysheet"));
		}
		
		void PopulateTypes_G()
		{
			MimeTypes.push(MimeMap("g2w", "application/vnd.geoplan"));
			MimeTypes.push(MimeMap("g3", "image/g3fax"));
			MimeTypes.push(MimeMap("g3w", "application/vnd.geospace"));
			MimeTypes.push(MimeMap("gac", "application/vnd.groove-account"));
			MimeTypes.push(MimeMap("gam", "application/x-tads"));
			MimeTypes.push(MimeMap("gbr", "application/rpki-ghostbusters"));
			MimeTypes.push(MimeMap("gca", "application/x-gca-compressed"));
			MimeTypes.push(MimeMap("gdl", "model/vnd.gdl"));
			MimeTypes.push(MimeMap("geo", "application/vnd.dynageo"));
			MimeTypes.push(MimeMap("gex", "application/vnd.geometry-explorer"));
			MimeTypes.push(MimeMap("ggb", "application/vnd.geogebra.file"));
			MimeTypes.push(MimeMap("ggt", "application/vnd.geogebra.tool"));
			MimeTypes.push(MimeMap("ghf", "application/vnd.groove-help"));
			MimeTypes.push(MimeMap("gif", "image/gif"));
			MimeTypes.push(MimeMap("gim", "application/vnd.groove-identity-message"));
			MimeTypes.push(MimeMap("gml", "application/gml+xml"));
			MimeTypes.push(MimeMap("gmx", "application/vnd.gmx"));
			MimeTypes.push(MimeMap("gnumeric", "application/x-gnumeric"));
			MimeTypes.push(MimeMap("gph", "application/vnd.flographit"));
			MimeTypes.push(MimeMap("gpx", "application/gpx+xml"));
			MimeTypes.push(MimeMap("gqf", "application/vnd.grafeq"));
			MimeTypes.push(MimeMap("gqs", "application/vnd.grafeq"));
			MimeTypes.push(MimeMap("gram", "application/srgs"));
			MimeTypes.push(MimeMap("gramps", "application/x-gramps-xml"));
			MimeTypes.push(MimeMap("gre", "application/vnd.geometry-explorer"));
			MimeTypes.push(MimeMap("grv", "application/vnd.groove-injector"));
			MimeTypes.push(MimeMap("grxml", "application/srgs+xml"));
			MimeTypes.push(MimeMap("gsf", "application/x-font-ghostscript"));
			MimeTypes.push(MimeMap("gtar", "application/x-gtar"));
			MimeTypes.push(MimeMap("gtm", "application/vnd.groove-tool-message"));
			MimeTypes.push(MimeMap("gtw", "model/vnd.gtw"));
			MimeTypes.push(MimeMap("gv", "text/vnd.graphviz"));
			MimeTypes.push(MimeMap("gxf", "application/gxf"));
			MimeTypes.push(MimeMap("gxt", "application/vnd.geonext"));
		}
		
		void PopulateTypes_H()
		{
			MimeTypes.push(MimeMap("h", "text/x-c"));
			MimeTypes.push(MimeMap("h261", "video/h261"));
			MimeTypes.push(MimeMap("h263", "video/h263"));
			MimeTypes.push(MimeMap("h264", "video/h264"));
			MimeTypes.push(MimeMap("hal", "application/vnd.hal+xml"));
			MimeTypes.push(MimeMap("hbci", "application/vnd.hbci"));
			MimeTypes.push(MimeMap("hdf", "application/x-hdf"));
			MimeTypes.push(MimeMap("hh", "text/x-c"));
			MimeTypes.push(MimeMap("hlp", "application/winhlp"));
			MimeTypes.push(MimeMap("hpgl", "application/vnd.hp-hpgl"));
			MimeTypes.push(MimeMap("hpid", "application/vnd.hp-hpid"));
			MimeTypes.push(MimeMap("hps", "application/vnd.hp-hps"));
			MimeTypes.push(MimeMap("hqx", "application/mac-binhex40"));
			MimeTypes.push(MimeMap("htke", "application/vnd.kenameaapp"));
			MimeTypes.push(MimeMap("htm", "text/html"));
			MimeTypes.push(MimeMap("html", "text/html"));
			MimeTypes.push(MimeMap("hvd", "application/vnd.yamaha.hv-dic"));
			MimeTypes.push(MimeMap("hvp", "application/vnd.yamaha.hv-voice"));
			MimeTypes.push(MimeMap("hvs", "application/vnd.yamaha.hv-script"));
		}
		
		void PopulateTypes_I()
		{
			MimeTypes.push(MimeMap("i2g", "application/vnd.intergeo"));
			MimeTypes.push(MimeMap("icc", "application/vnd.iccprofile"));
			MimeTypes.push(MimeMap("ice", "x-conference/x-cooltalk"));
			MimeTypes.push(MimeMap("icm", "application/vnd.iccprofile"));
			MimeTypes.push(MimeMap("ico", "image/x-icon"));
			MimeTypes.push(MimeMap("ics", "text/calendar"));
			MimeTypes.push(MimeMap("ief", "image/ief"));
			MimeTypes.push(MimeMap("ifb", "text/calendar"));
			MimeTypes.push(MimeMap("ifm", "application/vnd.shana.informed.formdata"));
			MimeTypes.push(MimeMap("iges", "model/iges"));
			MimeTypes.push(MimeMap("igl", "application/vnd.igloader"));
			MimeTypes.push(MimeMap("igm", "application/vnd.insors.igm"));
			MimeTypes.push(MimeMap("igs", "model/iges"));
			MimeTypes.push(MimeMap("igx", "application/vnd.micrografx.igx"));
			MimeTypes.push(MimeMap("iif", "application/vnd.shana.informed.interchange"));
			MimeTypes.push(MimeMap("imp", "application/vnd.accpac.simply.imp"));
			MimeTypes.push(MimeMap("ims", "application/vnd.ms-ims"));
			MimeTypes.push(MimeMap("in", "text/plain"));
			MimeTypes.push(MimeMap("ink", "application/inkml+xml"));
			MimeTypes.push(MimeMap("inkml", "application/inkml+xml"));
			MimeTypes.push(MimeMap("install", "application/x-install-instructions"));
			MimeTypes.push(MimeMap("iota", "application/vnd.astraea-software.iota"));
			MimeTypes.push(MimeMap("ipfix", "application/ipfix"));
			MimeTypes.push(MimeMap("ipk", "application/vnd.shana.informed.package"));
			MimeTypes.push(MimeMap("irm", "application/vnd.ibm.rights-management"));
			MimeTypes.push(MimeMap("irp", "application/vnd.irepository.package+xml"));
			MimeTypes.push(MimeMap("iso", "application/x-iso9660-image"));
			MimeTypes.push(MimeMap("itp", "application/vnd.shana.informed.formtemplate"));
			MimeTypes.push(MimeMap("ivp", "application/vnd.immervision-ivp"));
			MimeTypes.push(MimeMap("ivu", "application/vnd.immervision-ivu"));
		}
		
		void PopulateTypes_J()
		{
			MimeTypes.push(MimeMap("jad", "text/vnd.sun.j2me.app-descriptor"));
			MimeTypes.push(MimeMap("jam", "application/vnd.jam"));
			MimeTypes.push(MimeMap("jar", "application/java-archive"));
			MimeTypes.push(MimeMap("java", "text/x-java-source"));
			MimeTypes.push(MimeMap("jisp", "application/vnd.jisp"));
			MimeTypes.push(MimeMap("jlt", "application/vnd.hp-jlyt"));
			MimeTypes.push(MimeMap("jnlp", "application/x-java-jnlp-file"));
			MimeTypes.push(MimeMap("joda", "application/vnd.joost.joda-archive"));
			MimeTypes.push(MimeMap("jpe", "image/jpeg"));
			MimeTypes.push(MimeMap("jpeg", "image/jpeg"));
			MimeTypes.push(MimeMap("jpg", "image/jpeg"));
			MimeTypes.push(MimeMap("jpgm", "video/jpm"));
			MimeTypes.push(MimeMap("jpgv", "video/jpeg"));
			MimeTypes.push(MimeMap("jpm", "video/jpm"));
			MimeTypes.push(MimeMap("js", "application/javascript"));
			MimeTypes.push(MimeMap("json", "application/json"));
			MimeTypes.push(MimeMap("jsonml", "application/jsonml+json"));
		}
		
		void PopulateTypes_K()
		{
			MimeTypes.push(MimeMap("kar", "audio/midi"));
			MimeTypes.push(MimeMap("karbon", "application/vnd.kde.karbon"));
			MimeTypes.push(MimeMap("kfo", "application/vnd.kde.kformula"));
			MimeTypes.push(MimeMap("kia", "application/vnd.kidspiration"));
			MimeTypes.push(MimeMap("kml", "application/vnd.google-earth.kml+xml"));
			MimeTypes.push(MimeMap("kmz", "application/vnd.google-earth.kmz"));
			MimeTypes.push(MimeMap("kne", "application/vnd.kinar"));
			MimeTypes.push(MimeMap("knp", "application/vnd.kinar"));
			MimeTypes.push(MimeMap("kon", "application/vnd.kde.kontour"));
			MimeTypes.push(MimeMap("kpr", "application/vnd.kde.kpresenter"));
			MimeTypes.push(MimeMap("kpt", "application/vnd.kde.kpresenter"));
			MimeTypes.push(MimeMap("kpxx", "application/vnd.ds-keypoint"));
			MimeTypes.push(MimeMap("ksp", "application/vnd.kde.kspread"));
			MimeTypes.push(MimeMap("ktr", "application/vnd.kahootz"));
			MimeTypes.push(MimeMap("ktx", "image/ktx"));
			MimeTypes.push(MimeMap("ktz", "application/vnd.kahootz"));
			MimeTypes.push(MimeMap("kwd", "application/vnd.kde.kword"));
			MimeTypes.push(MimeMap("kwt", "application/vnd.kde.kword"));
		}
		
		void PopulateTypes_L()
		{
			MimeTypes.push(MimeMap("lasxml", "application/vnd.las.las+xml"));
			MimeTypes.push(MimeMap("latex", "application/x-latex"));
			MimeTypes.push(MimeMap("lbd", "application/vnd.llamagraphics.life-balance.desktop"));
			MimeTypes.push(MimeMap("lbe", "application/vnd.llamagraphics.life-balance.exchange+xml"));
			MimeTypes.push(MimeMap("les", "application/vnd.hhe.lesson-player"));
			MimeTypes.push(MimeMap("lha", "application/x-lzh-compressed"));
			MimeTypes.push(MimeMap("link66", "application/vnd.route66.link66+xml"));
			MimeTypes.push(MimeMap("list", "text/plain"));
			MimeTypes.push(MimeMap("list3820", "application/vnd.ibm.modcap"));
			MimeTypes.push(MimeMap("listafp", "application/vnd.ibm.modcap"));
			MimeTypes.push(MimeMap("lnk", "application/x-ms-shortcut"));
			MimeTypes.push(MimeMap("log", "text/plain"));
			MimeTypes.push(MimeMap("lostxml", "application/lost+xml"));
			MimeTypes.push(MimeMap("lrf", "application/octet-stream"));
			MimeTypes.push(MimeMap("lrm", "application/vnd.ms-lrm"));
			MimeTypes.push(MimeMap("ltf", "application/vnd.frogans.ltf"));
			MimeTypes.push(MimeMap("lvp", "audio/vnd.lucent.voice"));
			MimeTypes.push(MimeMap("lwp", "application/vnd.lotus-wordpro"));
			MimeTypes.push(MimeMap("lzh", "application/x-lzh-compressed"));
		}
		
		void PopulateTypes_M()
		{
			MimeTypes.push(MimeMap("m13", "application/x-msmediaview"));
			MimeTypes.push(MimeMap("m14", "application/x-msmediaview"));
			MimeTypes.push(MimeMap("m1v", "video/mpeg"));
			MimeTypes.push(MimeMap("m21", "application/mp21"));
			MimeTypes.push(MimeMap("m2a", "audio/mpeg"));
			MimeTypes.push(MimeMap("m2v", "video/mpeg"));
			MimeTypes.push(MimeMap("m3a", "audio/mpeg"));
			MimeTypes.push(MimeMap("m3u", "audio/x-mpegurl"));
			MimeTypes.push(MimeMap("m3u8", "application/vnd.apple.mpegurl"));
			MimeTypes.push(MimeMap("m4u", "video/vnd.mpegurl"));
			MimeTypes.push(MimeMap("m4v", "video/x-m4v"));
			MimeTypes.push(MimeMap("ma", "application/mathematica"));
			MimeTypes.push(MimeMap("mads", "application/mads+xml"));
			MimeTypes.push(MimeMap("mag", "application/vnd.ecowin.chart"));
			MimeTypes.push(MimeMap("maker", "application/vnd.framemaker"));
			MimeTypes.push(MimeMap("man", "text/troff"));
			MimeTypes.push(MimeMap("mar", "application/octet-stream"));
			MimeTypes.push(MimeMap("mathml", "application/mathml+xml"));
			MimeTypes.push(MimeMap("mb", "application/mathematica"));
			MimeTypes.push(MimeMap("mbk", "application/vnd.mobius.mbk"));
			MimeTypes.push(MimeMap("mbox", "application/mbox"));
			MimeTypes.push(MimeMap("mc1", "application/vnd.medcalcdata"));
			MimeTypes.push(MimeMap("mcd", "application/vnd.mcd"));
			MimeTypes.push(MimeMap("mcurl", "text/vnd.curl.mcurl"));
			MimeTypes.push(MimeMap("mdb", "application/x-msaccess"));
			MimeTypes.push(MimeMap("mdi", "image/vnd.ms-modi"));
			MimeTypes.push(MimeMap("me", "text/troff"));
			MimeTypes.push(MimeMap("mesh", "model/mesh"));
			MimeTypes.push(MimeMap("meta4", "application/metalink4+xml"));
			MimeTypes.push(MimeMap("metalink", "application/metalink+xml"));
			MimeTypes.push(MimeMap("mets", "application/mets+xml"));
			MimeTypes.push(MimeMap("mfm", "application/vnd.mfmp"));
			MimeTypes.push(MimeMap("mft", "application/rpki-manifest"));
			MimeTypes.push(MimeMap("mgp", "application/vnd.osgeo.mapguide.package"));
			MimeTypes.push(MimeMap("mgz", "application/vnd.proteus.magazine"));
			MimeTypes.push(MimeMap("mid", "audio/midi"));
			MimeTypes.push(MimeMap("midi", "audio/midi"));
			MimeTypes.push(MimeMap("mie", "application/x-mie"));
			MimeTypes.push(MimeMap("mif", "application/vnd.mif"));
			MimeTypes.push(MimeMap("mime", "message/rfc822"));
			MimeTypes.push(MimeMap("mj2", "video/mj2"));
			MimeTypes.push(MimeMap("mjp2", "video/mj2"));
			MimeTypes.push(MimeMap("mk3d", "video/x-matroska"));
			MimeTypes.push(MimeMap("mka", "audio/x-matroska"));
			MimeTypes.push(MimeMap("mks", "video/x-matroska"));
			MimeTypes.push(MimeMap("mkv", "video/x-matroska"));
			MimeTypes.push(MimeMap("mlp", "application/vnd.dolby.mlp"));
			MimeTypes.push(MimeMap("mmd", "application/vnd.chipnuts.karaoke-mmd"));
			MimeTypes.push(MimeMap("mmf", "application/vnd.smaf"));
			MimeTypes.push(MimeMap("mmr", "image/vnd.fujixerox.edmics-mmr"));
			MimeTypes.push(MimeMap("mng", "video/x-mng"));
			MimeTypes.push(MimeMap("mny", "application/x-msmoney"));
			MimeTypes.push(MimeMap("mobi", "application/x-mobipocket-ebook"));
			MimeTypes.push(MimeMap("mods", "application/mods+xml"));
			MimeTypes.push(MimeMap("mov", "video/quicktime"));
			MimeTypes.push(MimeMap("movie", "video/x-sgi-movie"));
			MimeTypes.push(MimeMap("mp2", "audio/mpeg"));
			MimeTypes.push(MimeMap("mp21", "application/mp21"));
			MimeTypes.push(MimeMap("mp2a", "audio/mpeg"));
			MimeTypes.push(MimeMap("mp3", "audio/mpeg"));
			MimeTypes.push(MimeMap("mp4", "video/mp4"));
			MimeTypes.push(MimeMap("mp4a", "audio/mp4"));
			MimeTypes.push(MimeMap("mp4s", "application/mp4"));
			MimeTypes.push(MimeMap("mp4v", "video/mp4"));
			MimeTypes.push(MimeMap("mpc", "application/vnd.mophun.certificate"));
			MimeTypes.push(MimeMap("mpe", "video/mpeg"));
			MimeTypes.push(MimeMap("mpeg", "video/mpeg"));
			MimeTypes.push(MimeMap("mpg", "video/mpeg"));
			MimeTypes.push(MimeMap("mpg4", "video/mp4"));
			MimeTypes.push(MimeMap("mpga", "audio/mpeg"));
			MimeTypes.push(MimeMap("mpkg", "application/vnd.apple.installer+xml"));
			MimeTypes.push(MimeMap("mpm", "application/vnd.blueice.multipass"));
			MimeTypes.push(MimeMap("mpn", "application/vnd.mophun.application"));
			MimeTypes.push(MimeMap("mpp", "application/vnd.ms-project"));
			MimeTypes.push(MimeMap("mpt", "application/vnd.ms-project"));
			MimeTypes.push(MimeMap("mpy", "application/vnd.ibm.minipay"));
			MimeTypes.push(MimeMap("mqy", "application/vnd.mobius.mqy"));
			MimeTypes.push(MimeMap("mrc", "application/marc"));
			MimeTypes.push(MimeMap("mrcx", "application/marcxml+xml"));
			MimeTypes.push(MimeMap("ms", "text/troff"));
			MimeTypes.push(MimeMap("mscml", "application/mediaservercontrol+xml"));
			MimeTypes.push(MimeMap("mseed", "application/vnd.fdsn.mseed"));
			MimeTypes.push(MimeMap("mseq", "application/vnd.mseq"));
			MimeTypes.push(MimeMap("msf", "application/vnd.epson.msf"));
			MimeTypes.push(MimeMap("msh", "model/mesh"));
			MimeTypes.push(MimeMap("msi", "application/x-msdownload"));
			MimeTypes.push(MimeMap("msl", "application/vnd.mobius.msl"));
			MimeTypes.push(MimeMap("msty", "application/vnd.muvee.style"));
			MimeTypes.push(MimeMap("mts", "model/vnd.mts"));
			MimeTypes.push(MimeMap("mus", "application/vnd.musician"));
			MimeTypes.push(MimeMap("musicxml", "application/vnd.recordare.musicxml+xml"));
			MimeTypes.push(MimeMap("mvb", "application/x-msmediaview"));
			MimeTypes.push(MimeMap("mwf", "application/vnd.mfer"));
			MimeTypes.push(MimeMap("mxf", "application/mxf"));
			MimeTypes.push(MimeMap("mxl", "application/vnd.recordare.musicxml"));
			MimeTypes.push(MimeMap("mxml", "application/xv+xml"));
			MimeTypes.push(MimeMap("mxs", "application/vnd.triscape.mxs"));
			MimeTypes.push(MimeMap("mxu", "video/vnd.mpegurl"));
		}
		
		void PopulateTypes_N()
		{
			MimeTypes.push(MimeMap("n-gage", "application/vnd.nokia.n-gage.symbian.install"));
			MimeTypes.push(MimeMap("n3", "text/n3"));
			MimeTypes.push(MimeMap("nb", "application/mathematica"));
			MimeTypes.push(MimeMap("nbp", "application/vnd.wolfram.player"));
			MimeTypes.push(MimeMap("nc", "application/x-netcdf"));
			MimeTypes.push(MimeMap("ncx", "application/x-dtbncx+xml"));
			MimeTypes.push(MimeMap("nfo", "text/x-nfo"));
			MimeTypes.push(MimeMap("ngdat", "application/vnd.nokia.n-gage.data"));
			MimeTypes.push(MimeMap("nitf", "application/vnd.nitf"));
			MimeTypes.push(MimeMap("nlu", "application/vnd.neurolanguage.nlu"));
			MimeTypes.push(MimeMap("nml", "application/vnd.enliven"));
			MimeTypes.push(MimeMap("nnd", "application/vnd.noblenet-directory"));
			MimeTypes.push(MimeMap("nns", "application/vnd.noblenet-sealer"));
			MimeTypes.push(MimeMap("nnw", "application/vnd.noblenet-web"));
			MimeTypes.push(MimeMap("npx", "image/vnd.net-fpx"));
			MimeTypes.push(MimeMap("nsc", "application/x-conference"));
			MimeTypes.push(MimeMap("nsf", "application/vnd.lotus-notes"));
			MimeTypes.push(MimeMap("ntf", "application/vnd.nitf"));
			MimeTypes.push(MimeMap("nzb", "application/x-nzb"));
		}
		
		void PopulateTypes_O()
		{
			MimeTypes.push(MimeMap("oa2", "application/vnd.fujitsu.oasys2"));
			MimeTypes.push(MimeMap("oa3", "application/vnd.fujitsu.oasys3"));
			MimeTypes.push(MimeMap("oas", "application/vnd.fujitsu.oasys"));
			MimeTypes.push(MimeMap("obd", "application/x-msbinder"));
			MimeTypes.push(MimeMap("obj", "application/x-tgif"));
			MimeTypes.push(MimeMap("oda", "application/oda"));
			MimeTypes.push(MimeMap("odb", "application/vnd.oasis.opendocument.database"));
			MimeTypes.push(MimeMap("odc", "application/vnd.oasis.opendocument.chart"));
			MimeTypes.push(MimeMap("odf", "application/vnd.oasis.opendocument.formula"));
			MimeTypes.push(MimeMap("odft", "application/vnd.oasis.opendocument.formula-template"));
			MimeTypes.push(MimeMap("odg", "application/vnd.oasis.opendocument.graphics"));
			MimeTypes.push(MimeMap("odi", "application/vnd.oasis.opendocument.image"));
			MimeTypes.push(MimeMap("odm", "application/vnd.oasis.opendocument.text-master"));
			MimeTypes.push(MimeMap("odp", "application/vnd.oasis.opendocument.presentation"));
			MimeTypes.push(MimeMap("ods", "application/vnd.oasis.opendocument.spreadsheet"));
			MimeTypes.push(MimeMap("odt", "application/vnd.oasis.opendocument.text"));
			MimeTypes.push(MimeMap("oga", "audio/ogg"));
			MimeTypes.push(MimeMap("ogg", "audio/ogg"));
			MimeTypes.push(MimeMap("ogv", "video/ogg"));
			MimeTypes.push(MimeMap("ogx", "application/ogg"));
			MimeTypes.push(MimeMap("omdoc", "application/omdoc+xml"));
			MimeTypes.push(MimeMap("onepkg", "application/onenote"));
			MimeTypes.push(MimeMap("onetmp", "application/onenote"));
			MimeTypes.push(MimeMap("onetoc", "application/onenote"));
			MimeTypes.push(MimeMap("onetoc2", "application/onenote"));
			MimeTypes.push(MimeMap("opf", "application/oebps-package+xml"));
			MimeTypes.push(MimeMap("opml", "text/x-opml"));
			MimeTypes.push(MimeMap("oprc", "application/vnd.palm"));
			MimeTypes.push(MimeMap("org", "application/vnd.lotus-organizer"));
			MimeTypes.push(MimeMap("osf", "application/vnd.yamaha.openscoreformat"));
			MimeTypes.push(MimeMap("osfpvg", "application/vnd.yamaha.openscoreformat.osfpvg+xml"));
			MimeTypes.push(MimeMap("otc", "application/vnd.oasis.opendocument.chart-template"));
			MimeTypes.push(MimeMap("otf", "application/x-font-otf"));
			MimeTypes.push(MimeMap("otg", "application/vnd.oasis.opendocument.graphics-template"));
			MimeTypes.push(MimeMap("oth", "application/vnd.oasis.opendocument.text-web"));
			MimeTypes.push(MimeMap("oti", "application/vnd.oasis.opendocument.image-template"));
			MimeTypes.push(MimeMap("otp", "application/vnd.oasis.opendocument.presentation-template"));
			MimeTypes.push(MimeMap("ots", "application/vnd.oasis.opendocument.spreadsheet-template"));
			MimeTypes.push(MimeMap("ott", "application/vnd.oasis.opendocument.text-template"));
			MimeTypes.push(MimeMap("oxps", "application/oxps"));
			MimeTypes.push(MimeMap("oxt", "application/vnd.openofficeorg.extension"));
		}
		
		void PopulateTypes_P()
		{
			MimeTypes.push(MimeMap("p", "text/x-pascal"));
			MimeTypes.push(MimeMap("p10", "application/pkcs10"));
			MimeTypes.push(MimeMap("p12", "application/x-pkcs12"));
			MimeTypes.push(MimeMap("p7b", "application/x-pkcs7-certificates"));
			MimeTypes.push(MimeMap("p7c", "application/pkcs7-mime"));
			MimeTypes.push(MimeMap("p7m", "application/pkcs7-mime"));
			MimeTypes.push(MimeMap("p7r", "application/x-pkcs7-certreqresp"));
			MimeTypes.push(MimeMap("p7s", "application/pkcs7-signature"));
			MimeTypes.push(MimeMap("p8", "application/pkcs8"));
			MimeTypes.push(MimeMap("pas", "text/x-pascal"));
			MimeTypes.push(MimeMap("paw", "application/vnd.pawaafile"));
			MimeTypes.push(MimeMap("pbd", "application/vnd.powerbuilder6"));
			MimeTypes.push(MimeMap("pbm", "image/x-portable-bitmap"));
			MimeTypes.push(MimeMap("pcap", "application/vnd.tcpdump.pcap"));
			MimeTypes.push(MimeMap("pcf", "application/x-font-pcf"));
			MimeTypes.push(MimeMap("pcl", "application/vnd.hp-pcl"));
			MimeTypes.push(MimeMap("pclxl", "application/vnd.hp-pclxl"));
			MimeTypes.push(MimeMap("pct", "image/x-pict"));
			MimeTypes.push(MimeMap("pcurl", "application/vnd.curl.pcurl"));
			MimeTypes.push(MimeMap("pcx", "image/x-pcx"));
			MimeTypes.push(MimeMap("pdb", "application/vnd.palm"));
			MimeTypes.push(MimeMap("pdf", "application/pdf"));
			MimeTypes.push(MimeMap("pfa", "application/x-font-type1"));
			MimeTypes.push(MimeMap("pfb", "application/x-font-type1"));
			MimeTypes.push(MimeMap("pfm", "application/x-font-type1"));
			MimeTypes.push(MimeMap("pfr", "application/font-tdpfr"));
			MimeTypes.push(MimeMap("pfx", "application/x-pkcs12"));
			MimeTypes.push(MimeMap("pgm", "image/x-portable-graymap"));
			MimeTypes.push(MimeMap("pgn", "application/x-chess-pgn"));
			MimeTypes.push(MimeMap("pgp", "application/pgp-encrypted"));
			MimeTypes.push(MimeMap("pic", "image/x-pict"));
			MimeTypes.push(MimeMap("pkg", "application/octet-stream"));
			MimeTypes.push(MimeMap("pki", "application/pkixcmp"));
			MimeTypes.push(MimeMap("pkipath", "application/pkix-pkipath"));
			MimeTypes.push(MimeMap("plb", "application/vnd.3gpp.pic-bw-large"));
			MimeTypes.push(MimeMap("plc", "application/vnd.mobius.plc"));
			MimeTypes.push(MimeMap("plf", "application/vnd.pocketlearn"));
			MimeTypes.push(MimeMap("pls", "application/pls+xml"));
			MimeTypes.push(MimeMap("pml", "application/vnd.ctc-posml"));
			MimeTypes.push(MimeMap("png", "image/png"));
			MimeTypes.push(MimeMap("pnm", "image/x-portable-anymap"));
			MimeTypes.push(MimeMap("portpkg", "application/vnd.macports.portpkg"));
			MimeTypes.push(MimeMap("pot", "application/vnd.ms-powerpoint"));
			MimeTypes.push(MimeMap("potm", "application/vnd.ms-powerpoint.template.macroenabled.12"));
			MimeTypes.push(MimeMap("potx", "application/vnd.openxmlformats-officedocument.presentationml.template"));
			MimeTypes.push(MimeMap("ppam", "application/vnd.ms-powerpoint.addin.macroenabled.12"));
			MimeTypes.push(MimeMap("ppd", "application/vnd.cups-ppd"));
			MimeTypes.push(MimeMap("ppm", "image/x-portable-pixmap"));
			MimeTypes.push(MimeMap("pps", "application/vnd.ms-powerpoint"));
			MimeTypes.push(MimeMap("ppsm", "application/vnd.ms-powerpoint.slideshow.macroenabled.12"));
			MimeTypes.push(MimeMap("ppsx", "application/vnd.openxmlformats-officedocument.presentationml.slideshow"));
			MimeTypes.push(MimeMap("ppt", "application/vnd.ms-powerpoint"));
			MimeTypes.push(MimeMap("pptm", "application/vnd.ms-powerpoint.presentation.macroenabled.12"));
			MimeTypes.push(MimeMap("pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"));
			MimeTypes.push(MimeMap("pqa", "application/vnd.palm"));
			MimeTypes.push(MimeMap("prc", "application/x-mobipocket-ebook"));
			MimeTypes.push(MimeMap("pre", "application/vnd.lotus-freelance"));
			MimeTypes.push(MimeMap("prf", "application/pics-rules"));
			MimeTypes.push(MimeMap("ps", "application/postscript"));
			MimeTypes.push(MimeMap("psb", "application/vnd.3gpp.pic-bw-small"));
			MimeTypes.push(MimeMap("psd", "image/vnd.adobe.photoshop"));
			MimeTypes.push(MimeMap("psf", "application/x-font-linux-psf"));
			MimeTypes.push(MimeMap("pskcxml", "application/pskc+xml"));
			MimeTypes.push(MimeMap("ptid", "application/vnd.pvi.ptid1"));
			MimeTypes.push(MimeMap("pub", "application/x-mspublisher"));
			MimeTypes.push(MimeMap("pvb", "application/vnd.3gpp.pic-bw-var"));
			MimeTypes.push(MimeMap("pwn", "application/vnd.3m.post-it-notes"));
			MimeTypes.push(MimeMap("pya", "audio/vnd.ms-playready.media.pya"));
			MimeTypes.push(MimeMap("pyv", "video/vnd.ms-playready.media.pyv"));
		}
		
		void PopulateTypes_Q()
		{
			MimeTypes.push(MimeMap("qam", "application/vnd.epson.quickanime"));
			MimeTypes.push(MimeMap("qbo", "application/vnd.intu.qbo"));
			MimeTypes.push(MimeMap("qfx", "application/vnd.intu.qfx"));
			MimeTypes.push(MimeMap("qps", "application/vnd.publishare-delta-tree"));
			MimeTypes.push(MimeMap("qt", "video/quicktime"));
			MimeTypes.push(MimeMap("qwd", "application/vnd.quark.quarkxpress"));
			MimeTypes.push(MimeMap("qwt", "application/vnd.quark.quarkxpress"));
			MimeTypes.push(MimeMap("qxb", "application/vnd.quark.quarkxpress"));
			MimeTypes.push(MimeMap("qxd", "application/vnd.quark.quarkxpress"));
			MimeTypes.push(MimeMap("qxl", "application/vnd.quark.quarkxpress"));
			MimeTypes.push(MimeMap("qxt", "application/vnd.quark.quarkxpress"));
		}
		
		void PopulateTypes_R()
		{
			MimeTypes.push(MimeMap("ra", "audio/x-pn-realaudio"));
			MimeTypes.push(MimeMap("ram", "audio/x-pn-realaudio"));
			MimeTypes.push(MimeMap("rar", "application/x-rar-compressed"));
			MimeTypes.push(MimeMap("ras", "image/x-cmu-raster"));
			MimeTypes.push(MimeMap("rcprofile", "application/vnd.ipunplugged.rcprofile"));
			MimeTypes.push(MimeMap("rdf", "application/rdf+xml"));
			MimeTypes.push(MimeMap("rdz", "application/vnd.data-vision.rdz"));
			MimeTypes.push(MimeMap("rep", "application/vnd.businessobjects"));
			MimeTypes.push(MimeMap("res", "application/x-dtbresource+xml"));
			MimeTypes.push(MimeMap("rgb", "image/x-rgb"));
			MimeTypes.push(MimeMap("rif", "application/reginfo+xml"));
			MimeTypes.push(MimeMap("rip", "audio/vnd.rip"));
			MimeTypes.push(MimeMap("ris", "application/x-research-info-systems"));
			MimeTypes.push(MimeMap("rl", "application/resource-lists+xml"));
			MimeTypes.push(MimeMap("rlc", "image/vnd.fujixerox.edmics-rlc"));
			MimeTypes.push(MimeMap("rld", "application/resource-lists-diff+xml"));
			MimeTypes.push(MimeMap("rm", "application/vnd.rn-realmedia"));
			MimeTypes.push(MimeMap("rmi", "audio/midi"));
			MimeTypes.push(MimeMap("rmp", "audio/x-pn-realaudio-plugin"));
			MimeTypes.push(MimeMap("rms", "application/vnd.jcp.javame.midlet-rms"));
			MimeTypes.push(MimeMap("rmvb", "application/vnd.rn-realmedia-vbr"));
			MimeTypes.push(MimeMap("rnc", "application/relax-ng-compact-syntax"));
			MimeTypes.push(MimeMap("roa", "application/rpki-roa"));
			MimeTypes.push(MimeMap("roff", "text/troff"));
			MimeTypes.push(MimeMap("rp9", "application/vnd.cloanto.rp9"));
			MimeTypes.push(MimeMap("rpss", "application/vnd.nokia.radio-presets"));
			MimeTypes.push(MimeMap("rpst", "application/vnd.nokia.radio-preset"));
			MimeTypes.push(MimeMap("rq", "application/sparql-query"));
			MimeTypes.push(MimeMap("rs", "application/rls-services+xml"));
			MimeTypes.push(MimeMap("rsd", "application/rsd+xml"));
			MimeTypes.push(MimeMap("rss", "application/rss+xml"));
			MimeTypes.push(MimeMap("rtf", "application/rtf"));
			MimeTypes.push(MimeMap("rtx", "text/richtext"));
		}
		
		void PopulateTypes_S()
		{
			MimeTypes.push(MimeMap("s", "text/x-asm"));
			MimeTypes.push(MimeMap("s3m", "audio/s3m"));
			MimeTypes.push(MimeMap("saf", "application/vnd.yamaha.smaf-audio"));
			MimeTypes.push(MimeMap("sbml", "application/sbml+xml"));
			MimeTypes.push(MimeMap("sc", "application/vnd.ibm.secure-container"));
			MimeTypes.push(MimeMap("scd", "application/x-msschedule"));
			MimeTypes.push(MimeMap("scm", "application/vnd.lotus-screencam"));
			MimeTypes.push(MimeMap("scq", "application/scvp-cv-request"));
			MimeTypes.push(MimeMap("scs", "application/scvp-cv-response"));
			MimeTypes.push(MimeMap("scurl", "text/vnd.curl.scurl"));
			MimeTypes.push(MimeMap("sda", "application/vnd.stardivision.draw"));
			MimeTypes.push(MimeMap("sdc", "application/vnd.stardivision.calc"));
			MimeTypes.push(MimeMap("sdd", "application/vnd.stardivision.impress"));
			MimeTypes.push(MimeMap("sdkd", "application/vnd.solent.sdkm+xml"));
			MimeTypes.push(MimeMap("sdkm", "application/vnd.solent.sdkm+xml"));
			MimeTypes.push(MimeMap("sdp", "application/sdp"));
			MimeTypes.push(MimeMap("sdw", "application/vnd.stardivision.writer"));
			MimeTypes.push(MimeMap("see", "application/vnd.seemail"));
			MimeTypes.push(MimeMap("seed", "application/vnd.fdsn.seed"));
			MimeTypes.push(MimeMap("sema", "application/vnd.sema"));
			MimeTypes.push(MimeMap("semd", "application/vnd.semd"));
			MimeTypes.push(MimeMap("semf", "application/vnd.semf"));
			MimeTypes.push(MimeMap("ser", "application/java-serialized-object"));
			MimeTypes.push(MimeMap("setpay", "application/set-payment-initiation"));
			MimeTypes.push(MimeMap("setreg", "application/set-registration-initiation"));
			MimeTypes.push(MimeMap("sfd-hdstx", "application/vnd.hydrostatix.sof-data"));
			MimeTypes.push(MimeMap("sfs", "application/vnd.spotfire.sfs"));
			MimeTypes.push(MimeMap("sfv", "text/x-sfv"));
			MimeTypes.push(MimeMap("sgi", "image/sgi"));
			MimeTypes.push(MimeMap("sgl", "application/vnd.stardivision.writer-global"));
			MimeTypes.push(MimeMap("sgm", "text/sgml"));
			MimeTypes.push(MimeMap("sgml", "text/sgml"));
			MimeTypes.push(MimeMap("sh", "application/x-sh"));
			MimeTypes.push(MimeMap("shar", "application/x-shar"));
			MimeTypes.push(MimeMap("shf", "application/shf+xml"));
			MimeTypes.push(MimeMap("sid", "image/x-mrsid-image"));
			MimeTypes.push(MimeMap("sig", "application/pgp-signature"));
			MimeTypes.push(MimeMap("sil", "audio/silk"));
			MimeTypes.push(MimeMap("silo", "model/mesh"));
			MimeTypes.push(MimeMap("sis", "application/vnd.symbian.install"));
			MimeTypes.push(MimeMap("sisx", "application/vnd.symbian.install"));
			MimeTypes.push(MimeMap("sit", "application/x-stuffit"));
			MimeTypes.push(MimeMap("sitx", "application/x-stuffitx"));
			MimeTypes.push(MimeMap("skd", "application/vnd.koan"));
			MimeTypes.push(MimeMap("skm", "application/vnd.koan"));
			MimeTypes.push(MimeMap("skp", "application/vnd.koan"));
			MimeTypes.push(MimeMap("skt", "application/vnd.koan"));
			MimeTypes.push(MimeMap("sldm", "application/vnd.ms-powerpoint.slide.macroenabled.12"));
			MimeTypes.push(MimeMap("sldx", "application/vnd.openxmlformats-officedocument.presentationml.slide"));
			MimeTypes.push(MimeMap("slt", "application/vnd.epson.salt"));
			MimeTypes.push(MimeMap("sm", "application/vnd.stepmania.stepchart"));
			MimeTypes.push(MimeMap("smf", "application/vnd.stardivision.math"));
			MimeTypes.push(MimeMap("smi", "application/smil+xml"));
			MimeTypes.push(MimeMap("smil", "application/smil+xml"));
			MimeTypes.push(MimeMap("smv", "video/x-smv"));
			MimeTypes.push(MimeMap("smzip", "application/vnd.stepmania.package"));
			MimeTypes.push(MimeMap("snd", "audio/basic"));
			MimeTypes.push(MimeMap("snf", "application/x-font-snf"));
			MimeTypes.push(MimeMap("so", "application/octet-stream"));
			MimeTypes.push(MimeMap("spc", "application/x-pkcs7-certificates"));
			MimeTypes.push(MimeMap("spf", "application/vnd.yamaha.smaf-phrase"));
			MimeTypes.push(MimeMap("spl", "application/x-futuresplash"));
			MimeTypes.push(MimeMap("spot", "text/vnd.in3d.spot"));
			MimeTypes.push(MimeMap("spp", "application/scvp-vp-response"));
			MimeTypes.push(MimeMap("spq", "application/scvp-vp-request"));
			MimeTypes.push(MimeMap("spx", "audio/ogg"));
			MimeTypes.push(MimeMap("sql", "application/x-sql"));
			MimeTypes.push(MimeMap("src", "application/x-wais-source"));
			MimeTypes.push(MimeMap("srt", "application/x-subrip"));
			MimeTypes.push(MimeMap("sru", "application/sru+xml"));
			MimeTypes.push(MimeMap("srx", "application/sparql-results+xml"));
			MimeTypes.push(MimeMap("ssdl", "application/ssdl+xml"));
			MimeTypes.push(MimeMap("sse", "application/vnd.kodak-descriptor"));
			MimeTypes.push(MimeMap("ssf", "application/vnd.epson.ssf"));
			MimeTypes.push(MimeMap("ssml", "application/ssml+xml"));
			MimeTypes.push(MimeMap("st", "application/vnd.sailingtracker.track"));
			MimeTypes.push(MimeMap("stc", "application/vnd.sun.xml.calc.template"));
			MimeTypes.push(MimeMap("std", "application/vnd.sun.xml.draw.template"));
			MimeTypes.push(MimeMap("stf", "application/vnd.wt.stf"));
			MimeTypes.push(MimeMap("sti", "application/vnd.sun.xml.impress.template"));
			MimeTypes.push(MimeMap("stk", "application/hyperstudio"));
			MimeTypes.push(MimeMap("stl", "application/vnd.ms-pki.stl"));
			MimeTypes.push(MimeMap("str", "application/vnd.pg.format"));
			MimeTypes.push(MimeMap("stw", "application/vnd.sun.xml.writer.template"));
			MimeTypes.push(MimeMap("sub", "text/vnd.dvb.subtitle"));
			MimeTypes.push(MimeMap("sus", "application/vnd.sus-calendar"));
			MimeTypes.push(MimeMap("susp", "application/vnd.sus-calendar"));
			MimeTypes.push(MimeMap("sv4cpio", "application/x-sv4cpio"));
			MimeTypes.push(MimeMap("sv4crc", "application/x-sv4crc"));
			MimeTypes.push(MimeMap("svc", "application/vnd.dvb.service"));
			MimeTypes.push(MimeMap("svd", "application/vnd.svd"));
			MimeTypes.push(MimeMap("svg", "image/svg+xml"));
			MimeTypes.push(MimeMap("svgz", "image/svg+xml"));
			MimeTypes.push(MimeMap("swa", "application/x-director"));
			MimeTypes.push(MimeMap("swf", "application/x-shockwave-flash"));
			MimeTypes.push(MimeMap("swi", "application/vnd.aristanetworks.swi"));
			MimeTypes.push(MimeMap("sxc", "application/vnd.sun.xml.calc"));
			MimeTypes.push(MimeMap("sxd", "application/vnd.sun.xml.draw"));
			MimeTypes.push(MimeMap("sxg", "application/vnd.sun.xml.writer.global"));
			MimeTypes.push(MimeMap("sxi", "application/vnd.sun.xml.impress"));
			MimeTypes.push(MimeMap("sxm", "application/vnd.sun.xml.math"));
			MimeTypes.push(MimeMap("sxw", "application/vnd.sun.xml.writer"));
		}
		
		void PopulateTypes_T()
		{
			MimeTypes.push(MimeMap("t", "text/troff"));
			MimeTypes.push(MimeMap("t3", "application/x-t3vm-image"));
			MimeTypes.push(MimeMap("taglet", "application/vnd.mynfc"));
			MimeTypes.push(MimeMap("tao", "application/vnd.tao.intent-module-archive"));
			MimeTypes.push(MimeMap("tar", "application/x-tar"));
			MimeTypes.push(MimeMap("tcap", "application/vnd.3gpp2.tcap"));
			MimeTypes.push(MimeMap("tcl", "application/x-tcl"));
			MimeTypes.push(MimeMap("teacher", "application/vnd.smart.teacher"));
			MimeTypes.push(MimeMap("tei", "application/tei+xml"));
			MimeTypes.push(MimeMap("teicorpus", "application/tei+xml"));
			MimeTypes.push(MimeMap("tex", "application/x-tex"));
			MimeTypes.push(MimeMap("texi", "application/x-texinfo"));
			MimeTypes.push(MimeMap("texinfo", "application/x-texinfo"));
			MimeTypes.push(MimeMap("text", "text/plain"));
			MimeTypes.push(MimeMap("tfi", "application/thraud+xml"));
			MimeTypes.push(MimeMap("tfm", "application/x-tex-tfm"));
			MimeTypes.push(MimeMap("tga", "image/x-tga"));
			MimeTypes.push(MimeMap("thmx", "application/vnd.ms-officetheme"));
			MimeTypes.push(MimeMap("tif", "image/tiff"));
			MimeTypes.push(MimeMap("tiff", "image/tiff"));
			MimeTypes.push(MimeMap("tmo", "application/vnd.tmobile-livetv"));
			MimeTypes.push(MimeMap("torrent", "application/x-bittorrent"));
			MimeTypes.push(MimeMap("tpl", "application/vnd.groove-tool-template"));
			MimeTypes.push(MimeMap("tpt", "application/vnd.trid.tpt"));
			MimeTypes.push(MimeMap("tr", "text/troff"));
			MimeTypes.push(MimeMap("tra", "application/vnd.trueapp"));
			MimeTypes.push(MimeMap("trm", "application/x-msterminal"));
			MimeTypes.push(MimeMap("tsd", "application/timestamped-data"));
			MimeTypes.push(MimeMap("tsv", "text/tab-separated-values"));
			MimeTypes.push(MimeMap("ttc", "application/x-font-ttf"));
			MimeTypes.push(MimeMap("ttf", "application/x-font-ttf"));
			MimeTypes.push(MimeMap("ttl", "text/turtle"));
			MimeTypes.push(MimeMap("twd", "application/vnd.simtech-mindmapper"));
			MimeTypes.push(MimeMap("twds", "application/vnd.simtech-mindmapper"));
			MimeTypes.push(MimeMap("txd", "application/vnd.genomatix.tuxedo"));
			MimeTypes.push(MimeMap("txf", "application/vnd.mobius.txf"));
			MimeTypes.push(MimeMap("txt", "text/plain"));
		}
		
		void PopulateTypes_U()
		{
			MimeTypes.push(MimeMap("u32", "application/x-authorware-bin"));
			MimeTypes.push(MimeMap("udeb", "application/x-debian-package"));
			MimeTypes.push(MimeMap("ufd", "application/vnd.ufdl"));
			MimeTypes.push(MimeMap("ufdl", "application/vnd.ufdl"));
			MimeTypes.push(MimeMap("ulx", "application/x-glulx"));
			MimeTypes.push(MimeMap("umj", "application/vnd.umajin"));
			MimeTypes.push(MimeMap("unityweb", "application/vnd.unity"));
			MimeTypes.push(MimeMap("uoml", "application/vnd.uoml+xml"));
			MimeTypes.push(MimeMap("uri", "text/uri-list"));
			MimeTypes.push(MimeMap("uris", "text/uri-list"));
			MimeTypes.push(MimeMap("urls", "text/uri-list"));
			MimeTypes.push(MimeMap("ustar", "application/x-ustar"));
			MimeTypes.push(MimeMap("utz", "application/vnd.uiq.theme"));
			MimeTypes.push(MimeMap("uu", "text/x-uuencode"));
			MimeTypes.push(MimeMap("uva", "audio/vnd.dece.audio"));
			MimeTypes.push(MimeMap("uvd", "application/vnd.dece.data"));
			MimeTypes.push(MimeMap("uvf", "application/vnd.dece.data"));
			MimeTypes.push(MimeMap("uvg", "image/vnd.dece.graphic"));
			MimeTypes.push(MimeMap("uvh", "video/vnd.dece.hd"));
			MimeTypes.push(MimeMap("uvi", "image/vnd.dece.graphic"));
			MimeTypes.push(MimeMap("uvm", "video/vnd.dece.mobile"));
			MimeTypes.push(MimeMap("uvp", "video/vnd.dece.pd"));
			MimeTypes.push(MimeMap("uvs", "video/vnd.dece.sd"));
			MimeTypes.push(MimeMap("uvt", "application/vnd.dece.ttml+xml"));
			MimeTypes.push(MimeMap("uvu", "video/vnd.uvvu.mp4"));
			MimeTypes.push(MimeMap("uvv", "video/vnd.dece.video"));
			MimeTypes.push(MimeMap("uvva", "audio/vnd.dece.audio"));
			MimeTypes.push(MimeMap("uvvd", "application/vnd.dece.data"));
			MimeTypes.push(MimeMap("uvvf", "application/vnd.dece.data"));
			MimeTypes.push(MimeMap("uvvg", "image/vnd.dece.graphic"));
			MimeTypes.push(MimeMap("uvvh", "video/vnd.dece.hd"));
			MimeTypes.push(MimeMap("uvvi", "image/vnd.dece.graphic"));
			MimeTypes.push(MimeMap("uvvm", "video/vnd.dece.mobile"));
			MimeTypes.push(MimeMap("uvvp", "video/vnd.dece.pd"));
			MimeTypes.push(MimeMap("uvvs", "video/vnd.dece.sd"));
			MimeTypes.push(MimeMap("uvvt", "application/vnd.dece.ttml+xml"));
			MimeTypes.push(MimeMap("uvvu", "video/vnd.uvvu.mp4"));
			MimeTypes.push(MimeMap("uvvv", "video/vnd.dece.video"));
			MimeTypes.push(MimeMap("uvvx", "application/vnd.dece.unspecified"));
			MimeTypes.push(MimeMap("uvvz", "application/vnd.dece.zip"));
			MimeTypes.push(MimeMap("uvx", "application/vnd.dece.unspecified"));
			MimeTypes.push(MimeMap("uvz", "application/vnd.dece.zip"));
		}
		
		void PopulateTypes_V()
		{
			MimeTypes.push(MimeMap("vcard", "text/vcard"));
			MimeTypes.push(MimeMap("vcd", "application/x-cdlink"));
			MimeTypes.push(MimeMap("vcf", "text/x-vcard"));
			MimeTypes.push(MimeMap("vcg", "application/vnd.groove-vcard"));
			MimeTypes.push(MimeMap("vcs", "text/x-vcalendar"));
			MimeTypes.push(MimeMap("vcx", "application/vnd.vcx"));
			MimeTypes.push(MimeMap("vis", "application/vnd.visionary"));
			MimeTypes.push(MimeMap("viv", "video/vnd.vivo"));
			MimeTypes.push(MimeMap("vob", "video/x-ms-vob"));
			MimeTypes.push(MimeMap("vor", "application/vnd.stardivision.writer"));
			MimeTypes.push(MimeMap("vox", "application/x-authorware-bin"));
			MimeTypes.push(MimeMap("vrml", "model/vrml"));
			MimeTypes.push(MimeMap("vsd", "application/vnd.visio"));
			MimeTypes.push(MimeMap("vsf", "application/vnd.vsf"));
			MimeTypes.push(MimeMap("vss", "application/vnd.visio"));
			MimeTypes.push(MimeMap("vst", "application/vnd.visio"));
			MimeTypes.push(MimeMap("vsw", "application/vnd.visio"));
			MimeTypes.push(MimeMap("vtu", "model/vnd.vtu"));
			MimeTypes.push(MimeMap("vxml", "application/voicexml+xml"));
		}
		
		void PopulateTypes_W()
		{
			MimeTypes.push(MimeMap("w3d", "application/x-director"));
			MimeTypes.push(MimeMap("wad", "application/x-doom"));
			MimeTypes.push(MimeMap("wav", "audio/x-wav"));
			MimeTypes.push(MimeMap("wax", "audio/x-ms-wax"));
			MimeTypes.push(MimeMap("wbmp", "image/vnd.wap.wbmp"));
			MimeTypes.push(MimeMap("wbs", "application/vnd.criticaltools.wbs+xml"));
			MimeTypes.push(MimeMap("wbxml", "application/vnd.wap.wbxml"));
			MimeTypes.push(MimeMap("wcm", "application/vnd.ms-works"));
			MimeTypes.push(MimeMap("wdb", "application/vnd.ms-works"));
			MimeTypes.push(MimeMap("wdp", "image/vnd.ms-photo"));
			MimeTypes.push(MimeMap("weba", "audio/webm"));
			MimeTypes.push(MimeMap("webm", "video/webm"));
			MimeTypes.push(MimeMap("webp", "image/webp"));
			MimeTypes.push(MimeMap("wg", "application/vnd.pmi.widget"));
			MimeTypes.push(MimeMap("wgt", "application/widget"));
			MimeTypes.push(MimeMap("wks", "application/vnd.ms-works"));
			MimeTypes.push(MimeMap("wm", "video/x-ms-wm"));
			MimeTypes.push(MimeMap("wma", "audio/x-ms-wma"));
			MimeTypes.push(MimeMap("wmd", "application/x-ms-wmd"));
			MimeTypes.push(MimeMap("wmf", "application/x-msmetafile"));
			MimeTypes.push(MimeMap("wml", "text/vnd.wap.wml"));
			MimeTypes.push(MimeMap("wmlc", "application/vnd.wap.wmlc"));
			MimeTypes.push(MimeMap("wmls", "text/vnd.wap.wmlscript"));
			MimeTypes.push(MimeMap("wmlsc", "application/vnd.wap.wmlscriptc"));
			MimeTypes.push(MimeMap("wmv", "video/x-ms-wmv"));
			MimeTypes.push(MimeMap("wmx", "video/x-ms-wmx"));
			MimeTypes.push(MimeMap("wmz", "application/x-ms-wmz"));
			MimeTypes.push(MimeMap("woff", "application/x-font-woff"));
			MimeTypes.push(MimeMap("wpd", "application/vnd.wordperfect"));
			MimeTypes.push(MimeMap("wpl", "application/vnd.ms-wpl"));
			MimeTypes.push(MimeMap("wps", "application/vnd.ms-works"));
			MimeTypes.push(MimeMap("wqd", "application/vnd.wqd"));
			MimeTypes.push(MimeMap("wri", "application/x-mswrite"));
			MimeTypes.push(MimeMap("wrl", "model/vrml"));
			MimeTypes.push(MimeMap("wsdl", "application/wsdl+xml"));
			MimeTypes.push(MimeMap("wspolicy", "application/wspolicy+xml"));
			MimeTypes.push(MimeMap("wtb", "application/vnd.webturbo"));
			MimeTypes.push(MimeMap("wvx", "video/x-ms-wvx"));
		}
		
		void PopulateTypes_X()
		{
			MimeTypes.push(MimeMap("x32", "application/x-authorware-bin"));
			MimeTypes.push(MimeMap("x3d", "model/x3d+xml"));
			MimeTypes.push(MimeMap("x3db", "model/x3d+binary"));
			MimeTypes.push(MimeMap("x3dbz", "model/x3d+binary"));
			MimeTypes.push(MimeMap("x3dv", "model/x3d+vrml"));
			MimeTypes.push(MimeMap("x3dvz", "model/x3d+vrml"));
			MimeTypes.push(MimeMap("x3dz", "model/x3d+xml"));
			MimeTypes.push(MimeMap("xaml", "application/xaml+xml"));
			MimeTypes.push(MimeMap("xap", "application/x-silverlight-app"));
			MimeTypes.push(MimeMap("xar", "application/vnd.xara"));
			MimeTypes.push(MimeMap("xbap", "application/x-ms-xbap"));
			MimeTypes.push(MimeMap("xbd", "application/vnd.fujixerox.docuworks.binder"));
			MimeTypes.push(MimeMap("xbm", "image/x-xbitmap"));
			MimeTypes.push(MimeMap("xdf", "application/xcap-diff+xml"));
			MimeTypes.push(MimeMap("xdm", "application/vnd.syncml.dm+xml"));
			MimeTypes.push(MimeMap("xdp", "application/vnd.adobe.xdp+xml"));
			MimeTypes.push(MimeMap("xdssc", "application/dssc+xml"));
			MimeTypes.push(MimeMap("xdw", "application/vnd.fujixerox.docuworks"));
			MimeTypes.push(MimeMap("xenc", "application/xenc+xml"));
			MimeTypes.push(MimeMap("xer", "application/patch-ops-error+xml"));
			MimeTypes.push(MimeMap("xfdf", "application/vnd.adobe.xfdf"));
			MimeTypes.push(MimeMap("xfdl", "application/vnd.xfdl"));
			MimeTypes.push(MimeMap("xht", "application/xhtml+xml"));
			MimeTypes.push(MimeMap("xhtml", "application/xhtml+xml"));
			MimeTypes.push(MimeMap("xhvml", "application/xv+xml"));
			MimeTypes.push(MimeMap("xif", "image/vnd.xiff"));
			MimeTypes.push(MimeMap("xla", "application/vnd.ms-excel"));
			MimeTypes.push(MimeMap("xlam", "application/vnd.ms-excel.addin.macroenabled.12"));
			MimeTypes.push(MimeMap("xlc", "application/vnd.ms-excel"));
			MimeTypes.push(MimeMap("xlf", "application/x-xliff+xml"));
			MimeTypes.push(MimeMap("xlm", "application/vnd.ms-excel"));
			MimeTypes.push(MimeMap("xls", "application/vnd.ms-excel"));
			MimeTypes.push(MimeMap("xlsb", "application/vnd.ms-excel.sheet.binary.macroenabled.12"));
			MimeTypes.push(MimeMap("xlsm", "application/vnd.ms-excel.sheet.macroenabled.12"));
			MimeTypes.push(MimeMap("xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"));
			MimeTypes.push(MimeMap("xlt", "application/vnd.ms-excel"));
			MimeTypes.push(MimeMap("xltm", "application/vnd.ms-excel.template.macroenabled.12"));
			MimeTypes.push(MimeMap("xltx", "application/vnd.openxmlformats-officedocument.spreadsheetml.template"));
			MimeTypes.push(MimeMap("xlw", "application/vnd.ms-excel"));
			MimeTypes.push(MimeMap("xm", "audio/xm"));
			MimeTypes.push(MimeMap("xml", "application/xml"));
			MimeTypes.push(MimeMap("xo", "application/vnd.olpc-sugar"));
			MimeTypes.push(MimeMap("xop", "application/xop+xml"));
			MimeTypes.push(MimeMap("xpi", "application/x-xpinstall"));
			MimeTypes.push(MimeMap("xpl", "application/xproc+xml"));
			MimeTypes.push(MimeMap("xpm", "image/x-xpixmap"));
			MimeTypes.push(MimeMap("xpr", "application/vnd.is-xpr"));
			MimeTypes.push(MimeMap("xps", "application/vnd.ms-xpsdocument"));
			MimeTypes.push(MimeMap("xpw", "application/vnd.intercon.formnet"));
			MimeTypes.push(MimeMap("xpx", "application/vnd.intercon.formnet"));
			MimeTypes.push(MimeMap("xsl", "application/xml"));
			MimeTypes.push(MimeMap("xslt", "application/xslt+xml"));
			MimeTypes.push(MimeMap("xsm", "application/vnd.syncml+xml"));
			MimeTypes.push(MimeMap("xspf", "application/xspf+xml"));
			MimeTypes.push(MimeMap("xul", "application/vnd.mozilla.xul+xml"));
			MimeTypes.push(MimeMap("xvm", "application/xv+xml"));
			MimeTypes.push(MimeMap("xvml", "application/xv+xml"));
			MimeTypes.push(MimeMap("xwd", "image/x-xwindowdump"));
			MimeTypes.push(MimeMap("xyz", "chemical/x-xyz"));
			MimeTypes.push(MimeMap("xz", "application/x-xz"));
		}
		
		void PopulateTypes_Y()
		{
			MimeTypes.push(MimeMap("yang", "application/yang"));
			MimeTypes.push(MimeMap("yin", "application/yin+xml"));
		}
		
		void PopulateTypes_Z()
		{
			MimeTypes.push(MimeMap("z1", "application/x-zmachine"));
			MimeTypes.push(MimeMap("z2", "application/x-zmachine"));
			MimeTypes.push(MimeMap("z3", "application/x-zmachine"));
			MimeTypes.push(MimeMap("z4", "application/x-zmachine"));
			MimeTypes.push(MimeMap("z5", "application/x-zmachine"));
			MimeTypes.push(MimeMap("z6", "application/x-zmachine"));
			MimeTypes.push(MimeMap("z7", "application/x-zmachine"));
			MimeTypes.push(MimeMap("z8", "application/x-zmachine"));
			MimeTypes.push(MimeMap("zaz", "application/vnd.zzazz.deck+xml"));
			MimeTypes.push(MimeMap("zip", "application/zip"));
			MimeTypes.push(MimeMap("zir", "application/vnd.zul"));
			MimeTypes.push(MimeMap("zirz", "application/vnd.zul"));
			MimeTypes.push(MimeMap("zmm", "application/vnd.handheld-entertainment+xml"));
		}
	}

	void PopulateMimeTypes()
	{
		boost::mutex::scoped_lock lock(MimeTypeMutex);
		if(MimeTypesPopulated)
		{
			return;
		}
		PopulateTypes_Num();
		PopulateTypes_A();
		PopulateTypes_B();
		PopulateTypes_C();
		PopulateTypes_D();
		PopulateTypes_E();
		PopulateTypes_F();
		PopulateTypes_G();
		PopulateTypes_H();
		PopulateTypes_I();
		PopulateTypes_J();
		PopulateTypes_K();
		PopulateTypes_L();
		PopulateTypes_M();
		PopulateTypes_N();
		PopulateTypes_O();
		PopulateTypes_P();
		PopulateTypes_Q();
		PopulateTypes_R();
		PopulateTypes_S();
		PopulateTypes_T();
		PopulateTypes_U();
		PopulateTypes_V();
		PopulateTypes_W();
		PopulateTypes_X();
		PopulateTypes_Y();
		PopulateTypes_Z();
		MimeTypesPopulated = true;
	}
}
