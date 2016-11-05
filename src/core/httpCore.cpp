
#include "httpCore.h"

void log_error(std::string message) {
    if (debug_mode) {
        perror(message.c_str());
    }
}

std::string ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

    return s;
}

// trim from end

std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());

    return s;
}

// trim from both ends

std::string trim(std::string s) {
    return ltrim(rtrim(s));
}

std::string extractMime(std::string fileName) {
    size_t pos = fileName.find_last_of('.');

    std::string extension;

    std::string mime_type = "text/plain, charset=us-ascii";

    if (pos == std::string::npos)
        extension = "";
    else
        extension = fileName.substr(pos + 1);


    if (extension == "")
        return mime_type;

        // image mime
    else if ((extension == "bmp") || (extension == "gif") || (extension == "png"))
        mime_type = "image/" + extension;
    else if ((extension == "jpeg") || (extension == "jpg"))
        mime_type = "image/jpeg";
    else if (extension == "ico")
        mime_type = "image/x-icon";

        // application mime
    else if ((extension == "bin") || (extension == "exe"))
        mime_type = "application/octet-stream";
    else if (extension == "xml")
        mime_type = "application/xml";

        // text mime
    else if (extension == "css")
        mime_type = "text/css";
    else if ((extension == "html") || (extension == "htm"))
        mime_type = "text/html";
    else if (extension == "txt")
        mime_type = "text/plain";


    return mime_type;
}

