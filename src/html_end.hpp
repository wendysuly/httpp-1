/*
 * html_start.hpp
 *
 *  Created on: Sep 2, 2012
 *      Author: jaedyn
 */

//Outside preprocessor ifchecks for easy folding.
//Inside preprocessor ifchecks enable the source file to be re-imported if something needs to be temporarily undefined, without having to redefine everything.
//Normal tags. Convention: The tag name, in lower case, with arguments. "tagname(...)"
#if true
		#undef a
		#undef abbr
		#undef address
		#undef area
		#undef article
		#undef aside
		#undef audio
		#undef b
		#undef base
		#undef bb
		#undef bdo
		#undef blockquote
		#undef body
		#undef br
		#undef button
		#undef canvas
		#undef caption
		#undef cite
		#undef code
		#undef col
		#undef colgroup
		#undef command
		#undef datagrid
		#undef datalist
		#undef dd
		#undef del
		#undef details
		#undef dfn
		#undef div
		#undef dl
		#undef dt
		#undef em
		#undef embed
		#undef eventsource
		#undef fieldset
		#undef figcaption
		#undef figure
		#undef footer
		#undef form
		#undef h1
		#undef h2
		#undef h3
		#undef h4
		#undef h5
		#undef h6
		#undef head
		#undef header
		#undef hgroup
		#undef hr
		#undef html
		#undef i
		#undef iframe
		#undef img
		#undef input
		#undef ins
		#undef kbd
		#undef keygen
		#undef label
		#undef legend
		#undef li
		#undef link
		#undef mark
		#undef map
		#undef menu
		#undef meta
		#undef meter
		#undef nav
		#undef noscript
		#undef object
		#undef ol
		#undef optgroup
		#undef option
		#undef output
		#undef p
		#undef param
		#undef pre
		#undef progress
		#undef q
		#undef ruby
		#undef rp
		#undef rt
		#undef samp
		#undef script
		#undef section
		#undef select
		#undef small
		#undef source
		#undef span
		#undef strong
		#undef style
		#undef sub
		#undef summary
		#undef sup
		#undef table
		#undef tbody
		#undef td
		#undef textarea
		#undef tfoot
		#undef th
		#undef thead
		#undef time
		#undef title
		#undef tr
		#undef ul
		#undef var
		#undef video
		#undef wbr
#endif

//Normal tags without arguments. No empty parens are required when using these. Convention: The tag name, in all capitals. "TAGNAME"
#if true
		#undef A
		#undef ABBR
		#undef ADDRESS
		#undef AREA
		#undef ARTICLE
		#undef ASIDE
		#undef AUDIO
		#undef B
		#undef BASE
		#undef BB
		#undef BDO
		#undef BLOCKQUOTE
		#undef BODY
		#undef BR
		#undef BUTTON
		#undef CANVAS
		#undef CAPTION
		#undef CITE
		#undef CODE
		#undef COL
		#undef COLGROUP
		#undef COMMAND
		#undef DATAGRID
		#undef DATALIST
		#undef DD
		#undef DEL
		#undef DETAILS
		#undef DFN
		#undef DIV
		#undef DL
		#undef DT
		#undef EM
		#undef EMBED
		#undef EVENTSOURCE
		#undef FIELDSET
		#undef FIGCAPTION
		#undef FIGURE
		#undef FOOTER
		#undef FORM
		#undef H1
		#undef H2
		#undef H3
		#undef H4
		#undef H5
		#undef H6
		#undef HEAD
		#undef HEADER
		#undef HGROUP
		#undef HR
		#undef HTML
		#undef I
		#undef IFRAME
		#undef IMG
		#undef INPUT
		#undef INS
		#undef KBD
		#undef KEYGEN
		#undef LABEL
		#undef LEGEND
		#undef LI
		#undef LINK
		#undef MARK
		#undef MAP
		#undef MENU
		#undef META
		#undef METER
		#undef NAV
		#undef NOSCRIPT
		#undef OBJECT
		#undef OL
		#undef OPTGROUP
		#undef OPTION
		#undef OUTPUT
		#undef P
		#undef PARAM
		#undef PRE
		#undef PROGRESS
		#undef Q
		#undef RUBY
		#undef RP
		#undef RT
		#undef SAMP
		#undef SCRIPT
		#undef SECTION
		#undef SELECT
		#undef SMALL
		#undef SOURCE
		#undef SPAN
		#undef STRONG
		#undef STYLE
		#undef SUB
		#undef SUMMARY
		#undef SUP
		#undef TABLE
		#undef TBODY
		#undef TD
		#undef TEXTAREA
		#undef TFOOT
		#undef TH
		#undef THEAD
		#undef TIME
		#undef TITLE
		#undef TR
		#undef UL
		#undef VAR
		#undef VIDEO
		#undef WBR
#endif

//Inline tags printed directly. Convention: $tagname(str, ...)
#if true
		#define $a(str, ...) HTTPP_I_TAG(str, a, __VA_ARGS__)
		#define $abbr(str, ...) HTTPP_I_TAG(str, abbr, __VA_ARGS__)
		#define $address(str, ...) HTTPP_I_TAG(str, address, __VA_ARGS__)
		#define $area(str, ...) HTTPP_I_TAG(str, area, __VA_ARGS__)
		#define $article(str, ...) HTTPP_I_TAG(str, article, __VA_ARGS__)
		#define $aside(str, ...) HTTPP_I_TAG(str, aside, __VA_ARGS__)
		#define $audio(str, ...) HTTPP_I_TAG(str, audio, __VA_ARGS__)
		#define $b(str, ...) HTTPP_I_TAG(str, b, __VA_ARGS__)
		#define $base(str, ...) HTTPP_I_TAG(str, base, __VA_ARGS__)
		#define $bb(str, ...) HTTPP_I_TAG(str, bb, __VA_ARGS__)
		#define $bdo(str, ...) HTTPP_I_TAG(str, bdo, __VA_ARGS__)
		#define $blockquote(str, ...) HTTPP_I_TAG(str, blockquote, __VA_ARGS__)
		#define $body(str, ...) HTTPP_I_TAG(str, body, __VA_ARGS__)
		#define $br(str, ...) HTTPP_I_TAG(str, br, __VA_ARGS__)
		#define $button(str, ...) HTTPP_I_TAG(str, button, __VA_ARGS__)
		#define $canvas(str, ...) HTTPP_I_TAG(str, canvas, __VA_ARGS__)
		#define $caption(str, ...) HTTPP_I_TAG(str, caption, __VA_ARGS__)
		#define $cite(str, ...) HTTPP_I_TAG(str, cite, __VA_ARGS__)
		#define $code(str, ...) HTTPP_I_TAG(str, code, __VA_ARGS__)
		#define $col(str, ...) HTTPP_I_TAG(str, col, __VA_ARGS__)
		#define $colgroup(str, ...) HTTPP_I_TAG(str, colgroup, __VA_ARGS__)
		#define $command(str, ...) HTTPP_I_TAG(str, command, __VA_ARGS__)
		#define $datagrid(str, ...) HTTPP_I_TAG(str, datagrid, __VA_ARGS__)
		#define $datalist(str, ...) HTTPP_I_TAG(str, datalist, __VA_ARGS__)
		#define $dd(str, ...) HTTPP_I_TAG(str, dd, __VA_ARGS__)
		#define $del(str, ...) HTTPP_I_TAG(str, del, __VA_ARGS__)
		#define $details(str, ...) HTTPP_I_TAG(str, details, __VA_ARGS__)
		#define $dfn(str, ...) HTTPP_I_TAG(str, dfn, __VA_ARGS__)
		#define $div(str, ...) HTTPP_I_TAG(str, div, __VA_ARGS__)
		#define $dl(str, ...) HTTPP_I_TAG(str, dl, __VA_ARGS__)
		#define $dt(str, ...) HTTPP_I_TAG(str, dt, __VA_ARGS__)
		#define $em(str, ...) HTTPP_I_TAG(str, em, __VA_ARGS__)
		#define $embed(str, ...) HTTPP_I_TAG(str, embed, __VA_ARGS__)
		#define $eventsource(str, ...) HTTPP_I_TAG(str, eventsource, __VA_ARGS__)
		#define $fieldset(str, ...) HTTPP_I_TAG(str, fieldset, __VA_ARGS__)
		#define $figcaption(str, ...) HTTPP_I_TAG(str, figcaption, __VA_ARGS__)
		#define $figure(str, ...) HTTPP_I_TAG(str, figure, __VA_ARGS__)
		#define $footer(str, ...) HTTPP_I_TAG(str, footer, __VA_ARGS__)
		#define $form(str, ...) HTTPP_I_TAG(str, form, __VA_ARGS__)
		#define $h1(str, ...) HTTPP_I_TAG(str, h1, __VA_ARGS__)
		#define $h2(str, ...) HTTPP_I_TAG(str, h2, __VA_ARGS__)
		#define $h3(str, ...) HTTPP_I_TAG(str, h3, __VA_ARGS__)
		#define $h4(str, ...) HTTPP_I_TAG(str, h4, __VA_ARGS__)
		#define $h5(str, ...) HTTPP_I_TAG(str, h5, __VA_ARGS__)
		#define $h6(str, ...) HTTPP_I_TAG(str, h6, __VA_ARGS__)
		#define $head(str, ...) HTTPP_I_TAG(str, head, __VA_ARGS__)
		#define $header(str, ...) HTTPP_I_TAG(str, header, __VA_ARGS__)
		#define $hgroup(str, ...) HTTPP_I_TAG(str, hgroup, __VA_ARGS__)
		#define $hr(str, ...) HTTPP_I_TAG(str, hr, __VA_ARGS__)
		#define $html(str, ...) HTTPP_I_TAG(str, html, __VA_ARGS__)
		#define $i(str, ...) HTTPP_I_TAG(str, i, __VA_ARGS__)
		#define $iframe(str, ...) HTTPP_I_TAG(str, iframe, __VA_ARGS__)
		#define $img(str, ...) HTTPP_I_TAG(str, img, __VA_ARGS__)
		#define $input(str, ...) HTTPP_I_TAG(str, input, __VA_ARGS__)
		#define $ins(str, ...) HTTPP_I_TAG(str, ins, __VA_ARGS__)
		#define $kbd(str, ...) HTTPP_I_TAG(str, kbd, __VA_ARGS__)
		#define $keygen(str, ...) HTTPP_I_TAG(str, keygen, __VA_ARGS__)
		#define $label(str, ...) HTTPP_I_TAG(str, label, __VA_ARGS__)
		#define $legend(str, ...) HTTPP_I_TAG(str, legend, __VA_ARGS__)
		#define $li(str, ...) HTTPP_I_TAG(str, li, __VA_ARGS__)
		#define $link(str, ...) HTTPP_I_TAG(str, link, __VA_ARGS__)
		#define $mark(str, ...) HTTPP_I_TAG(str, mark, __VA_ARGS__)
		#define $map(str, ...) HTTPP_I_TAG(str, map, __VA_ARGS__)
		#define $menu(str, ...) HTTPP_I_TAG(str, menu, __VA_ARGS__)
		#define $meta(str, ...) HTTPP_I_TAG(str, meta, __VA_ARGS__)
		#define $meter(str, ...) HTTPP_I_TAG(str, meter, __VA_ARGS__)
		#define $nav(str, ...) HTTPP_I_TAG(str, nav, __VA_ARGS__)
		#define $noscript(str, ...) HTTPP_I_TAG(str, noscript, __VA_ARGS__)
		#define $object(str, ...) HTTPP_I_TAG(str, object, __VA_ARGS__)
		#define $ol(str, ...) HTTPP_I_TAG(str, ol, __VA_ARGS__)
		#define $optgroup(str, ...) HTTPP_I_TAG(str, optgroup, __VA_ARGS__)
		#define $option(str, ...) HTTPP_I_TAG(str, option, __VA_ARGS__)
		#define $output(str, ...) HTTPP_I_TAG(str, output, __VA_ARGS__)
		#define $p(str, ...) HTTPP_I_TAG(str, p, __VA_ARGS__)
		#define $param(str, ...) HTTPP_I_TAG(str, param, __VA_ARGS__)
		#define $pre(str, ...) HTTPP_I_TAG(str, pre, __VA_ARGS__)
		#define $progress(str, ...) HTTPP_I_TAG(str, progress, __VA_ARGS__)
		#define $q(str, ...) HTTPP_I_TAG(str, q, __VA_ARGS__)
		#define $ruby(str, ...) HTTPP_I_TAG(str, ruby, __VA_ARGS__)
		#define $rp(str, ...) HTTPP_I_TAG(str, rp, __VA_ARGS__)
		#define $rt(str, ...) HTTPP_I_TAG(str, rt, __VA_ARGS__)
		#define $samp(str, ...) HTTPP_I_TAG(str, samp, __VA_ARGS__)
		#define $script(str, ...) HTTPP_I_TAG(str, script, __VA_ARGS__)
		#define $section(str, ...) HTTPP_I_TAG(str, section, __VA_ARGS__)
		#define $select(str, ...) HTTPP_I_TAG(str, select, __VA_ARGS__)
		#define $small(str, ...) HTTPP_I_TAG(str, small, __VA_ARGS__)
		#define $source(str, ...) HTTPP_I_TAG(str, source, __VA_ARGS__)
		#define $span(str, ...) HTTPP_I_TAG(str, span, __VA_ARGS__)
		#define $strong(str, ...) HTTPP_I_TAG(str, strong, __VA_ARGS__)
		#define $style(str, ...) HTTPP_I_TAG(str, style, __VA_ARGS__)
		#define $sub(str, ...) HTTPP_I_TAG(str, sub, __VA_ARGS__)
		#define $summary(str, ...) HTTPP_I_TAG(str, summary, __VA_ARGS__)
		#define $sup(str, ...) HTTPP_I_TAG(str, sup, __VA_ARGS__)
		#define $table(str, ...) HTTPP_I_TAG(str, table, __VA_ARGS__)
		#define $tbody(str, ...) HTTPP_I_TAG(str, tbody, __VA_ARGS__)
		#define $td(str, ...) HTTPP_I_TAG(str, td, __VA_ARGS__)
		#define $textarea(str, ...) HTTPP_I_TAG(str, textarea, __VA_ARGS__)
		#define $tfoot(str, ...) HTTPP_I_TAG(str, tfoot, __VA_ARGS__)
		#define $th(str, ...) HTTPP_I_TAG(str, th, __VA_ARGS__)
		#define $thead(str, ...) HTTPP_I_TAG(str, thead, __VA_ARGS__)
		#define $time(str, ...) HTTPP_I_TAG(str, time, __VA_ARGS__)
		#define $title(str, ...) HTTPP_I_TAG(str, title, __VA_ARGS__)
		#define $tr(str, ...) HTTPP_I_TAG(str, tr, __VA_ARGS__)
		#define $ul(str, ...) HTTPP_I_TAG(str, ul, __VA_ARGS__)
		#define $var(str, ...) HTTPP_I_TAG(str, var, __VA_ARGS__)
		#define $video(str, ...) HTTPP_I_TAG(str, video, __VA_ARGS__)
		#define $wbr(str, ...) HTTPP_I_TAG(str, wbr, __VA_ARGS__)
#endif

//Inline tags returning std::string for use in format strings. Convention: $$tagname(str, ...)
#if true
		#define $$a(str, ...) INLINE_TAG(str, a, __VA_ARGS__)
		#define $$abbr(str, ...) INLINE_TAG(str, abbr, __VA_ARGS__)
		#define $$address(str, ...) INLINE_TAG(str, address, __VA_ARGS__)
		#define $$area(str, ...) INLINE_TAG(str, area, __VA_ARGS__)
		#define $$article(str, ...) INLINE_TAG(str, article, __VA_ARGS__)
		#define $$aside(str, ...) INLINE_TAG(str, aside, __VA_ARGS__)
		#define $$audio(str, ...) INLINE_TAG(str, audio, __VA_ARGS__)
		#define $$b(str, ...) INLINE_TAG(str, b, __VA_ARGS__)
		#define $$base(str, ...) INLINE_TAG(str, base, __VA_ARGS__)
		#define $$bb(str, ...) INLINE_TAG(str, bb, __VA_ARGS__)
		#define $$bdo(str, ...) INLINE_TAG(str, bdo, __VA_ARGS__)
		#define $$blockquote(str, ...) INLINE_TAG(str, blockquote, __VA_ARGS__)
		#define $$body(str, ...) INLINE_TAG(str, body, __VA_ARGS__)
		#define $$br(str, ...) INLINE_TAG(str, br, __VA_ARGS__)
		#define $$button(str, ...) INLINE_TAG(str, button, __VA_ARGS__)
		#define $$canvas(str, ...) INLINE_TAG(str, canvas, __VA_ARGS__)
		#define $$caption(str, ...) INLINE_TAG(str, caption, __VA_ARGS__)
		#define $$cite(str, ...) INLINE_TAG(str, cite, __VA_ARGS__)
		#define $$code(str, ...) INLINE_TAG(str, code, __VA_ARGS__)
		#define $$col(str, ...) INLINE_TAG(str, col, __VA_ARGS__)
		#define $$colgroup(str, ...) INLINE_TAG(str, colgroup, __VA_ARGS__)
		#define $$command(str, ...) INLINE_TAG(str, command, __VA_ARGS__)
		#define $$datagrid(str, ...) INLINE_TAG(str, datagrid, __VA_ARGS__)
		#define $$datalist(str, ...) INLINE_TAG(str, datalist, __VA_ARGS__)
		#define $$dd(str, ...) INLINE_TAG(str, dd, __VA_ARGS__)
		#define $$del(str, ...) INLINE_TAG(str, del, __VA_ARGS__)
		#define $$details(str, ...) INLINE_TAG(str, details, __VA_ARGS__)
		#define $$dfn(str, ...) INLINE_TAG(str, dfn, __VA_ARGS__)
		#define $$div(str, ...) INLINE_TAG(str, div, __VA_ARGS__)
		#define $$dl(str, ...) INLINE_TAG(str, dl, __VA_ARGS__)
		#define $$dt(str, ...) INLINE_TAG(str, dt, __VA_ARGS__)
		#define $$em(str, ...) INLINE_TAG(str, em, __VA_ARGS__)
		#define $$embed(str, ...) INLINE_TAG(str, embed, __VA_ARGS__)
		#define $$eventsource(str, ...) INLINE_TAG(str, eventsource, __VA_ARGS__)
		#define $$fieldset(str, ...) INLINE_TAG(str, fieldset, __VA_ARGS__)
		#define $$figcaption(str, ...) INLINE_TAG(str, figcaption, __VA_ARGS__)
		#define $$figure(str, ...) INLINE_TAG(str, figure, __VA_ARGS__)
		#define $$footer(str, ...) INLINE_TAG(str, footer, __VA_ARGS__)
		#define $$form(str, ...) INLINE_TAG(str, form, __VA_ARGS__)
		#define $$h1(str, ...) INLINE_TAG(str, h1, __VA_ARGS__)
		#define $$h2(str, ...) INLINE_TAG(str, h2, __VA_ARGS__)
		#define $$h3(str, ...) INLINE_TAG(str, h3, __VA_ARGS__)
		#define $$h4(str, ...) INLINE_TAG(str, h4, __VA_ARGS__)
		#define $$h5(str, ...) INLINE_TAG(str, h5, __VA_ARGS__)
		#define $$h6(str, ...) INLINE_TAG(str, h6, __VA_ARGS__)
		#define $$head(str, ...) INLINE_TAG(str, head, __VA_ARGS__)
		#define $$header(str, ...) INLINE_TAG(str, header, __VA_ARGS__)
		#define $$hgroup(str, ...) INLINE_TAG(str, hgroup, __VA_ARGS__)
		#define $$hr(str, ...) INLINE_TAG(str, hr, __VA_ARGS__)
		#define $$html(str, ...) INLINE_TAG(str, html, __VA_ARGS__)
		#define $$i(str, ...) INLINE_TAG(str, i, __VA_ARGS__)
		#define $$iframe(str, ...) INLINE_TAG(str, iframe, __VA_ARGS__)
		#define $$img(str, ...) INLINE_TAG(str, img, __VA_ARGS__)
		#define $$input(str, ...) INLINE_TAG(str, input, __VA_ARGS__)
		#define $$ins(str, ...) INLINE_TAG(str, ins, __VA_ARGS__)
		#define $$kbd(str, ...) INLINE_TAG(str, kbd, __VA_ARGS__)
		#define $$keygen(str, ...) INLINE_TAG(str, keygen, __VA_ARGS__)
		#define $$label(str, ...) INLINE_TAG(str, label, __VA_ARGS__)
		#define $$legend(str, ...) INLINE_TAG(str, legend, __VA_ARGS__)
		#define $$li(str, ...) INLINE_TAG(str, li, __VA_ARGS__)
		#define $$link(str, ...) INLINE_TAG(str, link, __VA_ARGS__)
		#define $$mark(str, ...) INLINE_TAG(str, mark, __VA_ARGS__)
		#define $$map(str, ...) INLINE_TAG(str, map, __VA_ARGS__)
		#define $$menu(str, ...) INLINE_TAG(str, menu, __VA_ARGS__)
		#define $$meta(str, ...) INLINE_TAG(str, meta, __VA_ARGS__)
		#define $$meter(str, ...) INLINE_TAG(str, meter, __VA_ARGS__)
		#define $$nav(str, ...) INLINE_TAG(str, nav, __VA_ARGS__)
		#define $$noscript(str, ...) INLINE_TAG(str, noscript, __VA_ARGS__)
		#define $$object(str, ...) INLINE_TAG(str, object, __VA_ARGS__)
		#define $$ol(str, ...) INLINE_TAG(str, ol, __VA_ARGS__)
		#define $$optgroup(str, ...) INLINE_TAG(str, optgroup, __VA_ARGS__)
		#define $$option(str, ...) INLINE_TAG(str, option, __VA_ARGS__)
		#define $$output(str, ...) INLINE_TAG(str, output, __VA_ARGS__)
		#define $$p(str, ...) INLINE_TAG(str, p, __VA_ARGS__)
		#define $$param(str, ...) INLINE_TAG(str, param, __VA_ARGS__)
		#define $$pre(str, ...) INLINE_TAG(str, pre, __VA_ARGS__)
		#define $$progress(str, ...) INLINE_TAG(str, progress, __VA_ARGS__)
		#define $$q(str, ...) INLINE_TAG(str, q, __VA_ARGS__)
		#define $$ruby(str, ...) INLINE_TAG(str, ruby, __VA_ARGS__)
		#define $$rp(str, ...) INLINE_TAG(str, rp, __VA_ARGS__)
		#define $$rt(str, ...) INLINE_TAG(str, rt, __VA_ARGS__)
		#define $$samp(str, ...) INLINE_TAG(str, samp, __VA_ARGS__)
		#define $$script(str, ...) INLINE_TAG(str, script, __VA_ARGS__)
		#define $$section(str, ...) INLINE_TAG(str, section, __VA_ARGS__)
		#define $$select(str, ...) INLINE_TAG(str, select, __VA_ARGS__)
		#define $$small(str, ...) INLINE_TAG(str, small, __VA_ARGS__)
		#define $$source(str, ...) INLINE_TAG(str, source, __VA_ARGS__)
		#define $$span(str, ...) INLINE_TAG(str, span, __VA_ARGS__)
		#define $$strong(str, ...) INLINE_TAG(str, strong, __VA_ARGS__)
		#define $$style(str, ...) INLINE_TAG(str, style, __VA_ARGS__)
		#define $$sub(str, ...) INLINE_TAG(str, sub, __VA_ARGS__)
		#define $$summary(str, ...) INLINE_TAG(str, summary, __VA_ARGS__)
		#define $$sup(str, ...) INLINE_TAG(str, sup, __VA_ARGS__)
		#define $$table(str, ...) INLINE_TAG(str, table, __VA_ARGS__)
		#define $$tbody(str, ...) INLINE_TAG(str, tbody, __VA_ARGS__)
		#define $$td(str, ...) INLINE_TAG(str, td, __VA_ARGS__)
		#define $$textarea(str, ...) INLINE_TAG(str, textarea, __VA_ARGS__)
		#define $$tfoot(str, ...) INLINE_TAG(str, tfoot, __VA_ARGS__)
		#define $$th(str, ...) INLINE_TAG(str, th, __VA_ARGS__)
		#define $$thead(str, ...) INLINE_TAG(str, thead, __VA_ARGS__)
		#define $$time(str, ...) INLINE_TAG(str, time, __VA_ARGS__)
		#define $$title(str, ...) INLINE_TAG(str, title, __VA_ARGS__)
		#define $$tr(str, ...) INLINE_TAG(str, tr, __VA_ARGS__)
		#define $$ul(str, ...) INLINE_TAG(str, ul, __VA_ARGS__)
		#define $$var(str, ...) INLINE_TAG(str, var, __VA_ARGS__)
		#define $$video(str, ...) INLINE_TAG(str, video, __VA_ARGS__)
		#define $$wbr(str, ...) INLINE_TAG(str, wbr, __VA_ARGS__)
#endif

//XHTML-style self-closing tags with arguments. Convention: xtagname(...)
#if true
		#undef xa
		#undef xabbr
		#undef xaddress
		#undef xarea
		#undef xarticle
		#undef xaside
		#undef xaudio
		#undef xb
		#undef xbase
		#undef xbb
		#undef xbdo
		#undef xblockquote
		#undef xbody
		#undef xbr
		#undef xbutton
		#undef xcanvas
		#undef xcaption
		#undef xcite
		#undef xcode
		#undef xcol
		#undef xcolgroup
		#undef xcommand
		#undef xdatagrid
		#undef xdatalist
		#undef xdd
		#undef xdel
		#undef xdetails
		#undef xdfn
		#undef xdiv
		#undef xdl
		#undef xdt
		#undef xem
		#undef xembed
		#undef xeventsource
		#undef xfieldset
		#undef xfigcaption
		#undef xfigure
		#undef xfooter
		#undef xform
		#undef xh1
		#undef xh2
		#undef xh3
		#undef xh4
		#undef xh5
		#undef xh6
		#undef xhead
		#undef xheader
		#undef xhgroup
		#undef xhr
		#undef xhtml
		#undef xi
		#undef xiframe
		#undef ximg
		#undef xinput
		#undef xins
		#undef xkbd
		#undef xkeygen
		#undef xlabel
		#undef xlegend
		#undef xli
		#undef xlink
		#undef xmark
		#undef xmap
		#undef xmenu
		#undef xmeta
		#undef xmeter
		#undef xnav
		#undef xnoscript
		#undef xobject
		#undef xol
		#undef xoptgroup
		#undef xoption
		#undef xoutput
		#undef xp
		#undef xparam
		#undef xpre
		#undef xprogress
		#undef xq
		#undef xruby
		#undef xrp
		#undef xrt
		#undef xsamp
		#undef xscript
		#undef xsection
		#undef xselect
		#undef xsmall
		#undef xsource
		#undef xspan
		#undef xstrong
		#undef xstyle
		#undef xsub
		#undef xsummary
		#undef xsup
		#undef xtable
		#undef xtbody
		#undef xtd
		#undef xtextarea
		#undef xtfoot
		#undef xth
		#undef xthead
		#undef xtime
		#undef xtitle
		#undef xtr
		#undef xul
		#undef xvar
		#undef xvideo
		#undef xwbr
#endif

//XHTML-style self-closing tags with no arguments. Convention: xTAGNAME
#if true
		#undef xA
		#undef xABBR
		#undef xADDRESS
		#undef xAREA
		#undef xARTICLE
		#undef xASIDE
		#undef xAUDIO
		#undef xB
		#undef xBASE
		#undef xBB
		#undef xBDO
		#undef xBLOCKQUOTE
		#undef xBODY
		#undef xBR
		#undef xBUTTON
		#undef xCANVAS
		#undef xCAPTION
		#undef xCITE
		#undef xCODE
		#undef xCOL
		#undef xCOLGROUP
		#undef xCOMMAND
		#undef xDATAGRID
		#undef xDATALIST
		#undef xDD
		#undef xDEL
		#undef xDETAILS
		#undef xDFN
		#undef xDIV
		#undef xDL
		#undef xDT
		#undef xEM
		#undef xEMBED
		#undef xEVENTSOURCE
		#undef xFIELDSET
		#undef xFIGCAPTION
		#undef xFIGURE
		#undef xFOOTER
		#undef xFORM
		#undef xH1
		#undef xH2
		#undef xH3
		#undef xH4
		#undef xH5
		#undef xH6
		#undef xHEAD
		#undef xHEADER
		#undef xHGROUP
		#undef xHR
		#undef xHTML
		#undef xI
		#undef xIFRAME
		#undef xIMG
		#undef xINPUT
		#undef xINS
		#undef xKBD
		#undef xKEYGEN
		#undef xLABEL
		#undef xLEGEND
		#undef xLI
		#undef xLINK
		#undef xMARK
		#undef xMAP
		#undef xMENU
		#undef xMETA
		#undef xMETER
		#undef xNAV
		#undef xNOSCRIPT
		#undef xOBJECT
		#undef xOL
		#undef xOPTGROUP
		#undef xOPTION
		#undef xOUTPUT
		#undef xP
		#undef xPARAM
		#undef xPRE
		#undef xPROGRESS
		#undef xQ
		#undef xRUBY
		#undef xRP
		#undef xRT
		#undef xSAMP
		#undef xSCRIPT
		#undef xSECTION
		#undef xSELECT
		#undef xSMALL
		#undef xSOURCE
		#undef xSPAN
		#undef xSTRONG
		#undef xSTYLE
		#undef xSUB
		#undef xSUMMARY
		#undef xSUP
		#undef xTABLE
		#undef xTBODY
		#undef xTD
		#undef xTEXTAREA
		#undef xTFOOT
		#undef xTH
		#undef xTHEAD
		#undef xTIME
		#undef xTITLE
		#undef xTR
		#undef xUL
		#undef xVAR
		#undef xVIDEO
		#undef xWBR
#endif

//Inline tags with no body
#if true
		#undef ia
		#undef iabbr
		#undef iaddress
		#undef iarea
		#undef iarticle
		#undef iaside
		#undef iaudio
		#undef ib
		#undef ibase
		#undef ibb
		#undef ibdo
		#undef iblockquote
		#undef ibody
		#undef ibr
		#undef ibutton
		#undef icanvas
		#undef icaption
		#undef icite
		#undef icode
		#undef icol
		#undef icolgroup
		#undef icommand
		#undef idatagrid
		#undef idatalist
		#undef idd
		#undef idel
		#undef idetails
		#undef idfn
		#undef idiv
		#undef idl
		#undef idt
		#undef iem
		#undef iembed
		#undef ieventsource
		#undef ifieldset
		#undef ifigcaption
		#undef ifigure
		#undef ifooter
		#undef iform
		#undef ih1
		#undef ih2
		#undef ih3
		#undef ih4
		#undef ih5
		#undef ih6
		#undef ihead
		#undef iheader
		#undef ihgroup
		#undef ihr
		#undef ihtml
		#undef ii
		#undef iiframe
		#undef iimg
		#undef iinput
		#undef iins
		#undef ikbd
		#undef ikeygen
		#undef ilabel
		#undef ilegend
		#undef ili
		#undef ilink
		#undef imark
		#undef imap
		#undef imenu
		#undef imeta
		#undef imeter
		#undef inav
		#undef inoscript
		#undef iobject
		#undef iol
		#undef ioptgroup
		#undef ioption
		#undef ioutput
		#undef ip
		#undef iparam
		#undef ipre
		#undef iprogress
		#undef iq
		#undef iruby
		#undef irp
		#undef irt
		#undef isamp
		#undef iscript
		#undef isection
		#undef iselect
		#undef ismall
		#undef isource
		#undef ispan
		#undef istrong
		#undef istyle
		#undef isub
		#undef isummary
		#undef isup
		#undef itable
		#undef itbody
		#undef itd
		#undef itextarea
		#undef itfoot
		#undef ith
		#undef ithead
		#undef itime
		#undef ititle
		#undef itr
		#undef iul
		#undef ivar
		#undef ivideo
		#undef iwbr
#endif

//Inline tags with no body, no args
#if true
		#undef iA
		#undef iABBR
		#undef iADDRESS
		#undef iAREA
		#undef iARTICLE
		#undef iASIDE
		#undef iAUDIO
		#undef iB
		#undef iBASE
		#undef iBB
		#undef iBDO
		#undef iBLOCKQUOTE
		#undef iBODY
		#undef iBR
		#undef iBUTTON
		#undef iCANVAS
		#undef iCAPTION
		#undef iCITE
		#undef iCODE
		#undef iCOL
		#undef iCOLGROUP
		#undef iCOMMAND
		#undef iDATAGRID
		#undef iDATALIST
		#undef iDD
		#undef iDEL
		#undef iDETAILS
		#undef iDFN
		#undef iDIV
		#undef iDL
		#undef iDT
		#undef iEM
		#undef iEMBED
		#undef iEVENTSOURCE
		#undef iFIELDSET
		#undef iFIGCAPTION
		#undef iFIGURE
		#undef iFOOTER
		#undef iFORM
		#undef iH1
		#undef iH2
		#undef iH3
		#undef iH4
		#undef iH5
		#undef iH6
		#undef iHEAD
		#undef iHEADER
		#undef iHGROUP
		#undef iHR
		#undef iHTML
		#undef iI
		#undef iIFRAME
		#undef iIMG
		#undef iINPUT
		#undef iINS
		#undef iKBD
		#undef iKEYGEN
		#undef iLABEL
		#undef iLEGEND
		#undef iLI
		#undef iLINK
		#undef iMARK
		#undef iMAP
		#undef iMENU
		#undef iMETA
		#undef iMETER
		#undef iNAV
		#undef iNOSCRIPT
		#undef iOBJECT
		#undef iOL
		#undef iOPTGROUP
		#undef iOPTION
		#undef iOUTPUT
		#undef iP
		#undef iPARAM
		#undef iPRE
		#undef iPROGRESS
		#undef iQ
		#undef iRUBY
		#undef iRP
		#undef iRT
		#undef iSAMP
		#undef iSCRIPT
		#undef iSECTION
		#undef iSELECT
		#undef iSMALL
		#undef iSOURCE
		#undef iSPAN
		#undef iSTRONG
		#undef iSTYLE
		#undef iSUB
		#undef iSUMMARY
		#undef iSUP
		#undef iTABLE
		#undef iTBODY
		#undef iTD
		#undef iTEXTAREA
		#undef iTFOOT
		#undef iTH
		#undef iTHEAD
		#undef iTIME
		#undef iTITLE
		#undef iTR
		#undef iUL
		#undef iVAR
		#undef iVIDEO
		#undef iWBR
#endif

