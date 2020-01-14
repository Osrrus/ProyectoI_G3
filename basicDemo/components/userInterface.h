#pragma once
#include "../define.h"

using std::string;
typedef enum { NORMAL,NEGATIVE, GRAY_SCALE, BLACK_WITHE, GAUS, AVG } DEPLOY_TYPE;

class CUserInterface
{
    private:

        static CUserInterface * mInterface;
        TwBar *mUserInterface;
        CUserInterface(); 

    public:

        DEPLOY_TYPE m_currentDeploy;
        bool GPU;
        static CUserInterface * Instance();
        ~CUserInterface();
        void reshape(int, int);
        void show();
        void hide();
        string getDeployType();
       
};