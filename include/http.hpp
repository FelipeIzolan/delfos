#pragma once

#define RECV_BUFFER_SIZE 4096u

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>

#ifdef linux
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#endif

#ifdef _WIN32
#include <winsock2.h>
#endif


namespace HTTP {
    inline std::string mimeByExt(std::string ext) {
        if (ext == "*3gpp") return "audio/3gpp";
        if (ext == "*jpm") return "video/jpm";
        if (ext == "*mp3") return "audio/mp3";
        if (ext == "*rtf") return "text/rtf";
        if (ext == "*wav") return "audio/wave";
        if (ext == "*xml") return "text/xml";
        if (ext == "3g2") return "video/3gpp2";
        if (ext == "3gp") return "video/3gpp";
        if (ext == "3gpp") return "video/3gpp";
        if (ext == "ac") return "application/pkix-attr-cert";
        if (ext == "adp") return "audio/adpcm";
        if (ext == "ai") return "application/postscript";
        if (ext == "apng") return "image/apng";
        if (ext == "appcache") return "text/cache-manifest";
        if (ext == "asc") return "application/pgp-signature";
        if (ext == "atom") return "application/atom+xml";
        if (ext == "atomcat") return "application/atomcat+xml";
        if (ext == "atomsvc") return "application/atomsvc+xml";
        if (ext == "au") return "audio/basic";
        if (ext == "aw") return "application/applixware";
        if (ext == "bdoc") return "application/bdoc";
        if (ext == "bin") return "application/octet-stream";
        if (ext == "bmp") return "image/bmp";
        if (ext == "bpk") return "application/octet-stream";
        if (ext == "buffer") return "application/octet-stream";
        if (ext == "ccxml") return "application/ccxml+xml";
        if (ext == "cdmia") return "application/cdmi-capability";
        if (ext == "cdmic") return "application/cdmi-container";
        if (ext == "cdmid") return "application/cdmi-domain";
        if (ext == "cdmio") return "application/cdmi-object";
        if (ext == "cdmiq") return "application/cdmi-queue";
        if (ext == "cer") return "application/pkix-cert";
        if (ext == "cgm") return "image/cgm";
        if (ext == "class") return "application/java-vm";
        if (ext == "coffee") return "text/coffeescript";
        if (ext == "conf") return "text/plain";
        if (ext == "cpt") return "application/mac-compactpro";
        if (ext == "crl") return "application/pkix-crl";
        if (ext == "css") return "text/css";
        if (ext == "csv") return "text/csv";
        if (ext == "cu") return "application/cu-seeme";
        if (ext == "davmount") return "application/davmount+xml";
        if (ext == "dbk") return "application/docbook+xml";
        if (ext == "deb") return "application/octet-stream";
        if (ext == "def") return "text/plain";
        if (ext == "deploy") return "application/octet-stream";
        if (ext == "disposition-notification") return "message/disposition-notification";
        if (ext == "dist") return "application/octet-stream";
        if (ext == "distz") return "application/octet-stream";
        if (ext == "dll") return "application/octet-stream";
        if (ext == "dmg") return "application/octet-stream";
        if (ext == "dms") return "application/octet-stream";
        if (ext == "doc") return "application/msword";
        if (ext == "dot") return "application/msword";
        if (ext == "drle") return "image/dicom-rle";
        if (ext == "dssc") return "application/dssc+der";
        if (ext == "dtd") return "application/xml-dtd";
        if (ext == "dump") return "application/octet-stream";
        if (ext == "ear") return "application/java-archive";
        if (ext == "ecma") return "application/ecmascript";
        if (ext == "elc") return "application/octet-stream";
        if (ext == "emf") return "image/emf";
        if (ext == "eml") return "message/rfc822";
        if (ext == "emma") return "application/emma+xml";
        if (ext == "eps") return "application/postscript";
        if (ext == "epub") return "application/epub+zip";
        if (ext == "es") return "application/ecmascript";
        if (ext == "exe") return "application/octet-stream";
        if (ext == "exi") return "application/exi";
        if (ext == "exr") return "image/aces";
        if (ext == "ez") return "application/andrew-inset";
        if (ext == "fits") return "image/fits";
        if (ext == "g3") return "image/g3fax";
        if (ext == "gbr") return "application/rpki-ghostbusters";
        if (ext == "geojson") return "application/geo+json";
        if (ext == "gif") return "image/gif";
        if (ext == "glb") return "model/gltf-binary";
        if (ext == "gltf") return "model/gltf+json";
        if (ext == "gml") return "application/gml+xml";
        if (ext == "gpx") return "application/gpx+xml";
        if (ext == "gram") return "application/srgs";
        if (ext == "grxml") return "application/srgs+xml";
        if (ext == "gxf") return "application/gxf";
        if (ext == "gz") return "application/gzip";
        if (ext == "h261") return "video/h261";
        if (ext == "h263") return "video/h263";
        if (ext == "h264") return "video/h264";
        if (ext == "heic") return "image/heic";
        if (ext == "heics") return "image/heic-sequence";
        if (ext == "heif") return "image/heif";
        if (ext == "heifs") return "image/heif-sequence";
        if (ext == "hjson") return "application/hjson";
        if (ext == "hlp") return "application/winhlp";
        if (ext == "hqx") return "application/mac-binhex40";
        if (ext == "htm") return "text/html";
        if (ext == "html") return "text/html";
        if (ext == "ics") return "text/calendar";
        if (ext == "ief") return "image/ief";
        if (ext == "ifb") return "text/calendar";
        if (ext == "iges") return "model/iges";
        if (ext == "igs") return "model/iges";
        if (ext == "img") return "application/octet-stream";
        if (ext == "in") return "text/plain";
        if (ext == "ini") return "text/plain";
        if (ext == "ink") return "application/inkml+xml";
        if (ext == "inkml") return "application/inkml+xml";
        if (ext == "ipfix") return "application/ipfix";
        if (ext == "iso") return "application/octet-stream";
        if (ext == "jade") return "text/jade";
        if (ext == "jar") return "application/java-archive";
        if (ext == "jls") return "image/jls";
        if (ext == "jp2") return "image/jp2";
        if (ext == "jpe") return "image/jpeg";
        if (ext == "jpeg") return "image/jpeg";
        if (ext == "jpf") return "image/jpx";
        if (ext == "jpg") return "image/jpeg";
        if (ext == "jpg2") return "image/jp2";
        if (ext == "jpgm") return "video/jpm";
        if (ext == "jpgv") return "video/jpeg";
        if (ext == "jpm") return "image/jpm";
        if (ext == "jpx") return "image/jpx";
        if (ext == "js") return "application/javascript";
        if (ext == "json") return "application/json";
        if (ext == "json5") return "application/json5";
        if (ext == "jsonld") return "application/ld+json";
        if (ext == "jsonml") return "application/jsonml+json";
        if (ext == "jsx") return "text/jsx";
        if (ext == "kar") return "audio/midi";
        if (ext == "ktx") return "image/ktx";
        if (ext == "less") return "text/less";
        if (ext == "list") return "text/plain";
        if (ext == "litcoffee") return "text/coffeescript";
        if (ext == "log") return "text/plain";
        if (ext == "lostxml") return "application/lost+xml";
        if (ext == "lrf") return "application/octet-stream";
        if (ext == "m1v") return "video/mpeg";
        if (ext == "m21") return "application/mp21";
        if (ext == "m2a") return "audio/mpeg";
        if (ext == "m2v") return "video/mpeg";
        if (ext == "m3a") return "audio/mpeg";
        if (ext == "m4a") return "audio/mp4";
        if (ext == "m4p") return "application/mp4";
        if (ext == "ma") return "application/mathematica";
        if (ext == "mads") return "application/mads+xml";
        if (ext == "man") return "text/troff";
        if (ext == "manifest") return "text/cache-manifest";
        if (ext == "map") return "application/json";
        if (ext == "mar") return "application/octet-stream";
        if (ext == "markdown") return "text/markdown";
        if (ext == "mathml") return "application/mathml+xml";
        if (ext == "mb") return "application/mathematica";
        if (ext == "mbox") return "application/mbox";
        if (ext == "md") return "text/markdown";
        if (ext == "me") return "text/troff";
        if (ext == "mesh") return "model/mesh";
        if (ext == "meta4") return "application/metalink4+xml";
        if (ext == "metalink") return "application/metalink+xml";
        if (ext == "mets") return "application/mets+xml";
        if (ext == "mft") return "application/rpki-manifest";
        if (ext == "mid") return "audio/midi";
        if (ext == "midi") return "audio/midi";
        if (ext == "mime") return "message/rfc822";
        if (ext == "mj2") return "video/mj2";
        if (ext == "mjp2") return "video/mj2";
        if (ext == "mjs") return "application/javascript";
        if (ext == "mml") return "text/mathml";
        if (ext == "mods") return "application/mods+xml";
        if (ext == "mov") return "video/quicktime";
        if (ext == "mp2") return "audio/mpeg";
        if (ext == "mp21") return "application/mp21";
        if (ext == "mp2a") return "audio/mpeg";
        if (ext == "mp3") return "audio/mpeg";
        if (ext == "mp4") return "video/mp4";
        if (ext == "mp4a") return "audio/mp4";
        if (ext == "mp4s") return "application/mp4";
        if (ext == "mp4v") return "video/mp4";
        if (ext == "mpd") return "application/dash+xml";
        if (ext == "mpe") return "video/mpeg";
        if (ext == "mpeg") return "video/mpeg";
        if (ext == "mpg") return "video/mpeg";
        if (ext == "mpg4") return "video/mp4";
        if (ext == "mpga") return "audio/mpeg";
        if (ext == "mrc") return "application/marc";
        if (ext == "mrcx") return "application/marcxml+xml";
        if (ext == "ms") return "text/troff";
        if (ext == "mscml") return "application/mediaservercontrol+xml";
        if (ext == "msh") return "model/mesh";
        if (ext == "msi") return "application/octet-stream";
        if (ext == "msm") return "application/octet-stream";
        if (ext == "msp") return "application/octet-stream";
        if (ext == "mxf") return "application/mxf";
        if (ext == "mxml") return "application/xv+xml";
        if (ext == "n3") return "text/n3";
        if (ext == "nb") return "application/mathematica";
        if (ext == "oda") return "application/oda";
        if (ext == "oga") return "audio/ogg";
        if (ext == "ogg") return "audio/ogg";
        if (ext == "ogv") return "video/ogg";
        if (ext == "ogx") return "application/ogg";
        if (ext == "omdoc") return "application/omdoc+xml";
        if (ext == "onepkg") return "application/onenote";
        if (ext == "onetmp") return "application/onenote";
        if (ext == "onetoc") return "application/onenote";
        if (ext == "onetoc2") return "application/onenote";
        if (ext == "opf") return "application/oebps-package+xml";
        if (ext == "otf") return "font/otf";
        if (ext == "owl") return "application/rdf+xml";
        if (ext == "oxps") return "application/oxps";
        if (ext == "p10") return "application/pkcs10";
        if (ext == "p7c") return "application/pkcs7-mime";
        if (ext == "p7m") return "application/pkcs7-mime";
        if (ext == "p7s") return "application/pkcs7-signature";
        if (ext == "p8") return "application/pkcs8";
        if (ext == "pdf") return "application/pdf";
        if (ext == "pfr") return "application/font-tdpfr";
        if (ext == "pgp") return "application/pgp-encrypted";
        if (ext == "pkg") return "application/octet-stream";
        if (ext == "pki") return "application/pkixcmp";
        if (ext == "pkipath") return "application/pkix-pkipath";
        if (ext == "pls") return "application/pls+xml";
        if (ext == "png") return "image/png";
        if (ext == "prf") return "application/pics-rules";
        if (ext == "ps") return "application/postscript";
        if (ext == "pskcxml") return "application/pskc+xml";
        if (ext == "qt") return "video/quicktime";
        if (ext == "raml") return "application/raml+yaml";
        if (ext == "rdf") return "application/rdf+xml";
        if (ext == "rif") return "application/reginfo+xml";
        if (ext == "rl") return "application/resource-lists+xml";
        if (ext == "rld") return "application/resource-lists-diff+xml";
        if (ext == "rmi") return "audio/midi";
        if (ext == "rnc") return "application/relax-ng-compact-syntax";
        if (ext == "rng") return "application/xml";
        if (ext == "roa") return "application/rpki-roa";
        if (ext == "roff") return "text/troff";
        if (ext == "rq") return "application/sparql-query";
        if (ext == "rs") return "application/rls-services+xml";
        if (ext == "rsd") return "application/rsd+xml";
        if (ext == "rss") return "application/rss+xml";
        if (ext == "rtf") return "application/rtf";
        if (ext == "rtx") return "text/richtext";
        if (ext == "s3m") return "audio/s3m";
        if (ext == "sbml") return "application/sbml+xml";
        if (ext == "scq") return "application/scvp-cv-request";
        if (ext == "scs") return "application/scvp-cv-response";
        if (ext == "sdp") return "application/sdp";
        if (ext == "ser") return "application/java-serialized-object";
        if (ext == "setpay") return "application/set-payment-initiation";
        if (ext == "setreg") return "application/set-registration-initiation";
        if (ext == "sgi") return "image/sgi";
        if (ext == "sgm") return "text/sgml";
        if (ext == "sgml") return "text/sgml";
        if (ext == "shex") return "text/shex";
        if (ext == "shf") return "application/shf+xml";
        if (ext == "shtml") return "text/html";
        if (ext == "sig") return "application/pgp-signature";
        if (ext == "sil") return "audio/silk";
        if (ext == "silo") return "model/mesh";
        if (ext == "slim") return "text/slim";
        if (ext == "slm") return "text/slim";
        if (ext == "smi") return "application/smil+xml";
        if (ext == "smil") return "application/smil+xml";
        if (ext == "snd") return "audio/basic";
        if (ext == "so") return "application/octet-stream";
        if (ext == "spp") return "application/scvp-vp-response";
        if (ext == "spq") return "application/scvp-vp-request";
        if (ext == "spx") return "audio/ogg";
        if (ext == "sru") return "application/sru+xml";
        if (ext == "srx") return "application/sparql-results+xml";
        if (ext == "ssdl") return "application/ssdl+xml";
        if (ext == "ssml") return "application/ssml+xml";
        if (ext == "stk") return "application/hyperstudio";
        if (ext == "styl") return "text/stylus";
        if (ext == "stylus") return "text/stylus";
        if (ext == "svg") return "image/svg+xml";
        if (ext == "svgz") return "image/svg+xml";
        if (ext == "t") return "text/troff";
        if (ext == "t38") return "image/t38";
        if (ext == "tei") return "application/tei+xml";
        if (ext == "teicorpus") return "application/tei+xml";
        if (ext == "text") return "text/plain";
        if (ext == "tfi") return "application/thraud+xml";
        if (ext == "tfx") return "image/tiff-fx";
        if (ext == "tif") return "image/tiff";
        if (ext == "tiff") return "image/tiff";
        if (ext == "tr") return "text/troff";
        if (ext == "ts") return "video/mp2t";
        if (ext == "tsd") return "application/timestamped-data";
        if (ext == "tsv") return "text/tab-separated-values";
        if (ext == "ttc") return "font/collection";
        if (ext == "ttf") return "font/ttf";
        if (ext == "ttl") return "text/turtle";
        if (ext == "txt") return "text/plain";
        if (ext == "u8dsn") return "message/global-delivery-status";
        if (ext == "u8hdr") return "message/global-headers";
        if (ext == "u8mdn") return "message/global-disposition-notification";
        if (ext == "u8msg") return "message/global";
        if (ext == "uri") return "text/uri-list";
        if (ext == "uris") return "text/uri-list";
        if (ext == "urls") return "text/uri-list";
        if (ext == "vcard") return "text/vcard";
        if (ext == "vrml") return "model/vrml";
        if (ext == "vtt") return "text/vtt";
        if (ext == "vxml") return "application/voicexml+xml";
        if (ext == "war") return "application/java-archive";
        if (ext == "wasm") return "application/wasm";
        if (ext == "wav") return "audio/wav";
        if (ext == "weba") return "audio/webm";
        if (ext == "webm") return "video/webm";
        if (ext == "webmanifest") return "application/manifest+json";
        if (ext == "webp") return "image/webp";
        if (ext == "wgt") return "application/widget";
        if (ext == "wmf") return "image/wmf";
        if (ext == "woff") return "font/woff";
        if (ext == "woff2") return "font/woff2";
        if (ext == "wrl") return "model/vrml";
        if (ext == "wsdl") return "application/wsdl+xml";
        if (ext == "wspolicy") return "application/wspolicy+xml";
        if (ext == "x3d") return "model/x3d+xml";
        if (ext == "x3db") return "model/x3d+binary";
        if (ext == "x3dbz") return "model/x3d+binary";
        if (ext == "x3dv") return "model/x3d+vrml";
        if (ext == "x3dvz") return "model/x3d+vrml";
        if (ext == "x3dz") return "model/x3d+xml";
        if (ext == "xaml") return "application/xaml+xml";
        if (ext == "xdf") return "application/xcap-diff+xml";
        if (ext == "xdssc") return "application/dssc+xml";
        if (ext == "xenc") return "application/xenc+xml";
        if (ext == "xer") return "application/patch-ops-error+xml";
        if (ext == "xht") return "application/xhtml+xml";
        if (ext == "xhtml") return "application/xhtml+xml";
        if (ext == "xhvml") return "application/xv+xml";
        if (ext == "xm") return "audio/xm";
        if (ext == "xml") return "application/xml";
        if (ext == "xop") return "application/xop+xml";
        if (ext == "xpl") return "application/xproc+xml";
        if (ext == "xsd") return "application/xml";
        if (ext == "xsl") return "application/xml";
        if (ext == "xslt") return "application/xslt+xml";
        if (ext == "xspf") return "application/xspf+xml";
        if (ext == "xvm") return "application/xv+xml";
        if (ext == "xvml") return "application/xv+xml";
        if (ext == "yaml") return "text/yaml";
        if (ext == "yang") return "application/yang";
        if (ext == "yin") return "application/yin+xml";
        if (ext == "yml") return "text/yaml";
        if (ext == "zip") return "application/zip";
        return "";
    }

    inline std::string statusMessage(int code) {
        switch (code) {
        case 100: return "Continue";
        case 101: return "Switching Protocols";
        case 102: return "Processing";
        case 103: return "Early Hints";
        case 200: return "OK";
        case 201: return "Created";
        case 202: return "Accepted";
        case 203: return "Non-Authoritative Information";
        case 204: return "No Content";
        case 205: return "Reset Content";
        case 206: return "Partial Content";
        case 207: return "Multi-Status";
        case 208: return "Already Reported";
        case 226: return "IM Used";
        case 300: return "Multiple Choices";
        case 301: return "Moved Permanently";
        case 302: return "Found";
        case 303: return "See Other";
        case 304: return "Not Modified";
        case 305: return "Use Proxy";
        case 307: return "Temporary Redirect";
        case 308: return "Permanent Redirect";
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 402: return "Payment Required";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 406: return "Not Acceptable";
        case 407: return "Proxy Authentication Required";
        case 408: return "Request Timeout";
        case 409: return "Conflict";
        case 410: return "Gone";
        case 411: return "Length Required";
        case 412: return "Precondition Failed";
        case 413: return "Content Too Large";
        case 414: return "URI Too Long";
        case 415: return "Unsupported Media Type";
        case 416: return "Range Not Satisfiable";
        case 417: return "Expectation Failed";
        case 418: return "I'm a teapot";
        case 421: return "Misdirected Request";
        case 422: return "Unprocessable Content";
        case 423: return "Locked";
        case 424: return "Failed Dependency";
        case 425: return "Too Early";
        case 426: return "Upgrade Required";
        case 428: return "Precondition Required";
        case 429: return "Too Many Requests";
        case 431: return "Request Header Fields Too Large";
        case 451: return "Unavailable For Legal Reasons";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 503: return "Service Unavailable";
        case 504: return "Gateway Timeout";
        case 505: return "HTTP Version Not Supported";
        case 506: return "Variant Also Negotiates";
        case 507: return "Insufficient Storage";
        case 508: return "Loop Detected";
        case 510: return "Not Extended";
        case 511: return "Network Authentication Required";
        default: return std::string();
        }
    }

    inline std::string headers(std::map<std::string, std::string> h) {
        std::string s = "";

        for (auto i = h.begin(); i != h.end(); i++) {
            s += i->first + ": " + i->second + "\r\n";
        }

        return s;
    }
}


namespace HTTP {

    class Request {
    public:
        std::map<std::string, std::string> headers;
        std::string method;
        std::string body;
        std::string path;

        Request(char* buffer) {
            std::stringstream p(buffer);
            std::string line;

            for (int i = 0; i < 99; i++) { // https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers
                std::getline(p, line);

                if (i == 0) {
                    size_t s1 = line.find(" ");
                    size_t s2 = line.find("HTTP");

                    method = line.substr(0, s1);
                    path = line.substr(s1 + 1, s2 - 5);
                    path = path.substr(0, path.find(" "));
                    path = path.substr(0, path.find("?"));

                    continue;
                }

                size_t sep = line.find(":");
                if (sep == std::string::npos) { // empty-line
                  while (std::getline(p, line)) body += line;
                  break;
                }

                std::string key = line.substr(0, sep);
                std::string value = line.substr(sep + 2);

                headers.insert({ key, value });
            }
        }
    };


    class Response {
    public:
        std::map<std::string, std::string> headers;
        std::string body;
        int code = 200;
    };


    class Server {
    public:
        void setup(std::function<void(Request, Response*)> func) { handler = func; }

        void listen(uint16_t port) {
          #ifdef _WIN32
          SOCKET ssocket;
	        WSADATA wsa_data;
          #endif
          #ifdef linux
          int ssocket;
          #endif
 
          struct sockaddr_in saddress;
          char * soption = new char[BUFSIZ];
	        int ssize = sizeof(saddress);

          saddress.sin_port = htons(port); // network-byte-order - big-endian
          saddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // only local-client
          saddress.sin_family = AF_INET;

	        #ifdef _WIN32
	        if (WSAStartup(MAKEWORD(1,1), &wsa_data) != 0) {
		        perror("http.h -> WSAStartup failed.");
		        WSACleanup();
		        exit(1);
	        }
	        #endif

          if ((ssocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("http.h -> socket failed.");
		        #ifdef _WIN32
		        WSACleanup();
		        #endif
		        exit(1);
          }

          if (setsockopt(ssocket, SOL_SOCKET, SO_REUSEADDR, soption, sizeof(soption)) < 0) {
            perror("http.h -> socket option failed.");
		        #ifdef _WIN32
		        WSACleanup();
		        #endif
          	exit(1);
           }

          if (bind(ssocket, (struct sockaddr*)&saddress, ssize) < 0) {
            perror("http.h -> bind failed.");
		        #ifdef _WIN32
		        WSACleanup();
		        #endif
            exit(1);
          }

          if (::listen(ssocket, SOMAXCONN) < 0) {
            perror("http.h -> listen failed.");
		        #ifdef _WIN32
		        WSACleanup();
		        #endif
            exit(1);
          }

          while (1) {
            #ifdef _WIN32
            SOCKET csocket;
            #endif
            #ifdef linux
            int csocket;
            #endif
  		
            struct sockaddr_in caddress;
             
            #ifdef _WIN32
            int csize = sizeof(caddress);
            #endif
            #ifdef linux
            socklen_t csize = sizeof(caddress);
            #endif

            if ((csocket = accept(ssocket, (struct sockaddr*)&caddress, &csize)) < 0) {
              perror("http.h -> accept failed.");
              continue;
            }

            char * cbuffer = new char[RECV_BUFFER_SIZE];
            std::string sbuffer;

            if (recv(csocket, cbuffer, RECV_BUFFER_SIZE, 0) > 0) {
              Request req(cbuffer);
              Response res;

              handler(req, &res);
              sbuffer = AssemblyResponse(&res);

              if (send(csocket, sbuffer.c_str(), sbuffer.size(), 0) < 0) 
                perror("http.h -> send failed.");
            }
                
            #ifdef linux
            shutdown(csocket, SHUT_RDWR);
            close(csocket);
            #endif
            #ifdef _WIN32
		        shutdown(csocket, SD_SEND);
            closesocket(csocket);
            #endif

            memset(cbuffer, 0, RECV_BUFFER_SIZE);
          }

          #ifdef linux
          shutdown(ssocket, SHUT_RDWR);
          close(ssocket);
          #endif

          #ifdef _WIN32
          shutdown(ssocket, SD_SEND);
          closesocket(ssocket);
	        WSACleanup();
          #endif
        }

    protected:
        std::function<void(Request, Response*)> handler;
        std::string AssemblyResponse(Response * res) {
          return 
            "HTTP/1.1 " + std::to_string(res->code) + " " + statusMessage(res->code) + "\r\n" +
            headers(res->headers) +
            "\r\n" +
            res->body;
        }
    };

}
