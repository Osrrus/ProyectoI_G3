#include "UserInterface.h"
#include "Windows.h"
#include <Commdlg.h>

void TW_CALL CallbackLoad(void *clientData);
string loadPath();
void beginLoad(string path);

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
	//TwDefine("Menu position = '20 20'");
	TwDefine("Menu size = '220 320'");
	TwDefine("Menu visible = true");
	
	GPU = false;
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, NULL);

	TwEnumVal DeployType[] = { {NORMAL, "Normal"},{ NEGATIVE, "Negative" },{ GRAY_SCALE, "Gray Scale" },{ BLACK_WITHE, "Black And White" },
    { GAUS, "Laplace Gaus" },{ AVG, "Averague" } };
	TwType DeployTwType = TwDefineEnum("Fliter", DeployType, 6);

	TwAddVarRW(mUserInterface, "Deploy", DeployTwType, &m_currentDeploy, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Hardware Acceleration", TW_TYPE_BOOLCPP, &GPU, "");

	/*
	TwAddVarRW(mUserInterface, "Translation X", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Translation Y", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Translation Z", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Model' step=0.01 ");

	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Scale X", TW_TYPE_FLOAT, &mModelScale[0], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Scale Y", TW_TYPE_FLOAT, &mModelScale[1], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Scale Z", TW_TYPE_FLOAT, &mModelScale[2], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Scale All", TW_TYPE_FLOAT, &mScaleAll, " group='Model' step=0.01 ");*/

}

void TW_CALL CallbackLoad(void *clientData)
{
	string path = loadPath();
	if (path != "")
		beginLoad(path);
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
    
	return NULL;
}