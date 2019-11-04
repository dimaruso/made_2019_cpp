void find_token(const std::string &pr, const int len,
	void (*start)(int i), void(*end)(int i),
	void (*Ntoken)(const int &token),
	void(*Stoken)(const std::string &token));
