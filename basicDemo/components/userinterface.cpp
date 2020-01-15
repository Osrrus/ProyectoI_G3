#include "UserInterface.h"
#include "Windows.h"
#include <Commdlg.h>

void TW_CALL CallbackLoad(void *clientData);
void TW_CALL CallbackSave(void *clientData);

string loadPath();
void beginLoad(string path);
void beginSave();

CUserInterface * CUserInterface::mInterface = NULL;

CUserInterface * CUserInterface::Instance()
{
	if (!mInterface)
		mInterface = new CUserInterface();

	return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Menu");
	m_currentDeploy = NORMAL;

	TwDefine("Menu refresh = '0.0001f'");
	TwDefine("Menu resizable = true");
	TwDefine("Menu fontresizable = true");
	TwDefine("Menu movable = false");
	TwDefine("Menu size = '220 320'");
	TwDefine("Menu visible = true");
	kernelX = kernelY = 3;
	GPU = false;

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Width", TW_TYPE_INT32, &width, "readonly=true");
	TwAddVarRW(mUserInterface, "Height", TW_TYPE_INT32, &height, "readonly=true");
	TwAddVarRW(mUserInterface, "Bits per pixel", TW_TYPE_INT32, &pixels, "readonly=true");
	TwAddVarRW(mUserInterface, "Unique Colors", TW_TYPE_INT32, &uniqueColors, "readonly=true");

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, NULL);
	TwAddButton(mUserInterface, "Save", CallbackSave, NULL, NULL);
	
	TwAddSeparator(mUserInterface, "", NULL);
	TwEnumVal DeployType[] = { {NORMAL, "Normal"},{ NEGATIVE, "Negative" },{ GRAY_SCALE, "Gray Scale" },{ BLACK_WITHE, "Black And White" },
    { GAUS, "Laplace Gaus" },{ AVG, "Averague" },{SOBEL, "Sobel"},{PREWITT, "Prewitt"},{ROBERTS, "Roberts"},{TOON, "Toon"},{MEDIANA, "Mediana"}};
	TwType DeployTwType = TwDefineEnum("Fliter", DeployType, 11);

	TwAddVarRW(mUserInterface, "Deploy", DeployTwType, &m_currentDeploy, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Hardware Acceleration", TW_TYPE_BOOLCPP, &GPU, "");

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Kernel Size x", TW_TYPE_INT32, &kernelX, "min=1 max=7");
	TwAddVarRW(mUserInterface, "Kernel Size y", TW_TYPE_INT32, &kernelY, "min=1 max=7");

}

void TW_CALL CallbackLoad(void *clientData)
{
	string path = loadPath();
	if (path != "")
		beginLoad(path);
}

void TW_CALL CallbackSave(void *clientData){

	beginSave();
	
}

CUserInterface::~CUserInterface()
{

}

void CUserInterface::reshape( int windowWidth,  int windowHeight)
{
	TwWindowSize(windowWidth, windowHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

string loadPath()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "JPG Files(.jpg)\0*.jpg";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

string CUserInterface::getDeployType() {

	if (m_currentDeploy == NORMAL) return "normal";
	if (m_currentDeploy == NEGATIVE) return "negative";
	if (m_currentDeploy == GRAY_SCALE) return "grayScale";
	if (m_currentDeploy == BLACK_WITHE) return "blackWhite";
	if (m_currentDeploy == GAUS) return "gaus";
	if (m_currentDeploy == AVG) return "avg";
	if (m_currentDeploy == SOBEL) return "sobel";
	if (m_currentDeploy == PREWITT) return "prewitt";
	if (m_currentDeploy == ROBERTS) return "roberts";
	if (m_currentDeploy == TOON) return "toon";
	if (m_currentDeploy == MEDIANA) return "mediana";
    
	return NULL;
}