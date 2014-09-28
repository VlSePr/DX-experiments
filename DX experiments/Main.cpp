#include "DXUtilities.h"

class DXAppTest : public DXUAppUtilities
{
public:
	DXAppTest (HINSTANCE hinstance);
	~DXAppTest ();


	void Update (float dx) override;
	void Render (float dx) override;
};




int WINAPI WinMain (_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow)
{
	DXAppTest* appTest = new DXAppTest (hInstance);
	if (appTest->Init ())
	{
		return appTest->Run ();
	}

	return EXIT_FAILURE;
}

DXAppTest::DXAppTest (HINSTANCE hinstance) :DXUAppUtilities (hinstance)
{}

DXAppTest::~DXAppTest ()
{}

void DXAppTest::Update (float dx)
{}

void DXAppTest::Render (float dx)
{}
