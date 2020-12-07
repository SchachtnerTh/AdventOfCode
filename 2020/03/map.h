class terrain {
	private:
	int width;
	int height;
	char **terrainmap;
	
	public:
	terrain (char* source);
	~terrain();
	int getHeight();
	void test();
	bool isTree(int x, int y);
};