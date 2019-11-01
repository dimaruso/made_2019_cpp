using callback = bool(*) (int i);
using callbackntoken = int(*) (const int &token);
using callbackstoken = std::string(*) (const std::string &token);

void find_token(const std::string &pr, const int len,
	callback start, callback end, callbackntoken Ntoken, callbackstoken Stoken);