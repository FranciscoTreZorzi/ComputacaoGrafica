#include "Scene7.h"

CScene7::CScene7()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	
	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 100.0f, 100.0f, 3.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();	
	pTextures->CreateTextureClamp(0, "../Scene1/back.bmp");
	pTextures->CreateTextureClamp(1, "../Scene1/front.bmp");
	pTextures->CreateTextureClamp(2, "../Scene1/down.bmp");
	pTextures->CreateTextureClamp(3, "../Scene1/up.bmp");
	pTextures->CreateTextureClamp(4, "../Scene1/left.bmp");
	pTextures->CreateTextureClamp(5, "../Scene1/right.bmp");

	pTextures->CreateTextureLinear(6, "../Scene1/water.bmp");

	pTextures->CreateTextureTGA(7, "../Scene6/arvore.tga");
	pTextures->CreateTextureTGA(8, "../Scene6/cerca.tga");

	pTextures->CreateTextureTGA(9, "../Scene7/oak.tga");
	
	pTextures->CreateTextureMipMap(10, "../Scene7/ai.png");


	// Carrega o objeto
	pCena1 = NULL;
	pCena1 = new CModel_3DS();
	pCena1->Load("../Scene7/Cena1.3DS");


	// Carrega o objeto
	pCena2 = NULL;
	pCena2 = new CModel_3DS();
	pCena2->Load("../Scene7/Cena2.3DS");

	// Carrega o objeto
	pCena3 = NULL;
	pCena3 = new CModel_3DS();
	pCena3->Load("../Scene7/Cena3.3DS");

	// Carrega o objeto
	pCena4 = NULL;
	pCena4 = new CModel_3DS();
	pCena4->Load("../Scene7/Cena4.3DS");

	// Carrega o objeto
	pCena5 = NULL;
	pCena5 = new CModel_3DS();
	pCena5->Load("../Scene7/Cena5.3DS");

	// Carrega o objeto
	pCena6 = NULL;
	pCena6 = new CModel_3DS();
	pCena6->Load("../Scene7/Cena6.3DS");

	// Carrega o objeto casa
	pCena7 = NULL;
	pCena7 = new CModel_3DS();
	pCena7->Load("../Scene7/Cena7.3DS");

	// Carrega o objeto arvore
	pCena8 = NULL;
	pCena8 = new CModel_3DS();
	pCena8->Load("../Scene7/Cena8.3DS");

	// Carrega o objeto
	pCena9 = NULL;
	pCena9 = new CModel_3DS();
	pCena9->Load("../Scene7/Cena9.3DS");

	// Carrega o objeto
	pCena10 = NULL;
	pCena10 = new CModel_3DS();
	pCena10->Load("../Scene7/Cena10.3DS");


	// Carrega o objeto
	pCena11 = NULL;
	pCena11 = new CModel_3DS();
	pCena11->Load("../Scene7/Cena11.3DS");

	// Carrega o objeto
	pCena12 = NULL;
	pCena12 = new CModel_3DS();
	pCena12->Load("../Scene7/Cena12.3DS");

}


CScene7::~CScene7(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}	



	if (pCena1)
	{
		delete pCena1;
		pCena1 = NULL;
	}


	if (pCena2)
	{
		delete pCena2;
		pCena2 = NULL;
	}

	if (pCena3)
	{
		delete pCena3;
		pCena3 = NULL;
	}

	if (pCena4)
	{
		delete pCena4;
		pCena4 = NULL;
	}

	if (pCena5)
	{
		delete pCena5;
		pCena5 = NULL;
	}

	if (pCena6)
	{
		delete pCena6;
		pCena6 = NULL;
	}

	if (pCena7)
	{
		delete pCena7;
		pCena7 = NULL;
	}

	if (pCena8)
	{
		delete pCena8;
		pCena8 = NULL;
	}

	if (pCena9)
	{
		delete pCena9;
		pCena9 = NULL;
	}

	if (pCena10)
	{
		delete pCena10;
		pCena10 = NULL;
	}

	if (pCena11)
	{
		delete pCena11;
		pCena11 = NULL;
	}

	if (pCena12)
	{
		delete pCena12;
		pCena12 = NULL;
	}
}




int CScene7::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	// SkyBox
	CreateSkyBox(0.0f, 200.0f, 0.0f,
		3000.0f, 3000.0f, 3000.0f,
		pTextures);

	// Desenha neblina
	GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };
	glEnable(GL_FOG);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 20.0f);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.5f);
	glDisable(GL_FOG);

	// Desenha um tronco de arvore na mão
	glPushMatrix();
	glTranslatef(0.f, 10.f, -30.0f);
	pTextures->ApplyTexture(10);
	DrawLightCube();
	glPopMatrix();

	//glPushMatrix();
	//glTranslatef(10.0f, 20.0f, 10.0f);
	//pTextures->ApplyTexture(9);
	//DrawLightCube();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(10.0f, 30.0f, 10.0f);
	//glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	//pTextures->ApplyTexture(9);
	//DrawLightCube();
	//glPopMatrix();
	//fim do tronco desenhado na mão


	// Cena1
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena1->Draw();
	glPopMatrix();

	//Cena 2
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena2->Draw();
	glPopMatrix();

	//Cena 3
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena3->Draw();
	glPopMatrix();

	//Cena 4
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena4->Draw();
	glPopMatrix();

	//Cena 5
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena5->Draw();
	glPopMatrix();

	//Cena 6
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena6->Draw();
	glPopMatrix();

	//Cena 7
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena7->Draw();
	glPopMatrix();

	//Cena 8
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena8->Draw();
	glPopMatrix();

	//Cena 12
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	pCena12->Draw();
	glPopMatrix();

	//Cena 9
	//glPushMatrix();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	//pCena9->Draw();
	//glPopMatrix();


	//faz transparência 
	// Habilita Blending
	glEnable(GL_BLEND);
	// Configura função de Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	//Seta cor do quadrado vermelho
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	glPushMatrix();
	glTranslatef(17.0f, 12.0f, -61.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -2.0f);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, 2.0f, 0.0f);
	glVertex3f(-2.0f, 2.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);


	//faz transparencia vidro 2
	// Habilita Blending
	glEnable(GL_BLEND);
	// Configura função de Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Seta cor do quadrado vermelho
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	glPushMatrix();
	glTranslatef(17.0f, 12.0f, -68.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -2.0f);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, 2.0f, 0.0f);
	glVertex3f(-2.0f, 2.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);


	// Habilita Blending
	glEnable(GL_BLEND);
	// Configura função de Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);

	glPushAttrib(GL_TEXTURE_BIT);

	// Unidade de Textura 0
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	pTextures->ApplyTexture(6);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);


	// Unidade de Textura 1
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	pTextures->ApplyTexture(6);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	//agua
	glPushMatrix();
	glTranslatef(10.0f, 8.0f, -45.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fRenderPosY, 0.0f);
	glVertex3f(-16.5f, 0.0f, -30.5);

	glMultiTexCoord2f(GL_TEXTURE0, 5.0f, 0.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 5.0f + fRenderPosY, 0.0f);
	glVertex3f(-16.5f, 0.0f, 30.7f);

	glMultiTexCoord2f(GL_TEXTURE0, 5.0f, 5.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 5.0f + fRenderPosY, 5.0f);
	glVertex3f(16.5f, 0.0f, 30.5f);

	glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 5.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fRenderPosY, 5.0f);
	glVertex3f(16.5f, 0.0f, -30.5f);
	glEnd();
	glPopMatrix();

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();

	// Desabilita Blending
	glDisable(GL_BLEND);


	glDisable(GL_TEXTURE_2D);




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.002f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene7::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene7::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}



}

void CScene7::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene7::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void CScene7::DrawCube(float pX, float pY, float pZ,
	float rX, float rY, float rZ, float angle,
	float sX, float sY, float sZ,
	int texID)
{

	// Seta a textura ativa
	if (texID >= 0)
		pTextures->ApplyTexture(texID);

	glPushMatrix();
	glTranslatef(pX, pY, pZ);
	glRotatef(angle, rX, rY, rZ);
	glScalef(sX, sY, sZ);

	glBegin(GL_QUADS);
	// face frente
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, 0.5f);

	// face trás
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	
	// face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  -0.5f);

	glEnd();

	glPopMatrix();
}


void CScene7::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene7::CreateSkyBox(float x, float y, float z,
	float width, float height, float length,
	CTexture* pTextures)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();

	// Centraliza o Skybox em torno da posição especificada(x, y, z)
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Aplica a textura que representa a parte da frente do skybox (BACK map)
	pTextures->ApplyTexture(0);

	// Desenha face BACK do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (FRONT map)
	pTextures->ApplyTexture(1);

	// Desenha face FRONT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (DOWN map)
	pTextures->ApplyTexture(2);

	// Desenha face BOTTOM do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (UP map)
	pTextures->ApplyTexture(3);

	// Desenha face TOP do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (LEFT map)
	pTextures->ApplyTexture(4);

	// Desenha face LEFT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (RIGHT map)
	pTextures->ApplyTexture(5);

	// Desenha face RIGHT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();
}

void CScene7::DrawLightCube()
{

	glBegin(GL_QUADS);

	// face frente
	glm::vec3 N = CalculateQuadNormalVector(
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f)
	);
	glNormal3f(N.x, N.y, N.z);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// face trás
	N = CalculateQuadNormalVector(
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f)
	);
	glNormal3f(N.x, N.y, N.z);
	//glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

	// face direita
	N = CalculateQuadNormalVector(
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f)
	);
	glNormal3f(N.x, N.y, N.z);
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	N = CalculateQuadNormalVector(
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f)
	);
	glNormal3f(N.x, N.y, N.z);
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	N = CalculateQuadNormalVector(
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f)
	);
	glNormal3f(N.x, N.y, N.z);
	//glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	// face cima
	N = CalculateQuadNormalVector(
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f)
	);
	glNormal3f(N.x, N.y, N.z);
	//glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();


}

void CScene7::DrawLightPiramid()
{

	glBegin(GL_TRIANGLES);

	// face frente
	glm::vec3 N = CalculateTriangleNormalVector(
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 1.5f, 0.0f)
	);
	glNormal3f(N.x, N.y, N.z);
	glTexCoord2d(0.02f, 0.1f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.435f, 0.1f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.23f, 0.45f); glVertex3f(0.0f, 1.5f, 0.0f);



	// face trás
	N = CalculateTriangleNormalVector(
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 1.5f, 0.0f)
	);
	glNormal3f(N.x, N.y, N.z);
	glTexCoord2d(0.52f, 0.1f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.94f, 0.1f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.73f, 0.45f); glVertex3f(0.0f, 1.5f, 0.0f);



	// face direita
	N = CalculateTriangleNormalVector(
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 1.5f, 0.0f)
	);
	glNormal3f(N.x, N.y, N.z);
	glTexCoord2d(0.02f, 0.56f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.435f, 0.56f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.23f, 0.9f); glVertex3f(0.0f, 1.5f, 0.0f);



	// face esquerda
	N = CalculateTriangleNormalVector(
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 1.5f, 0.0f)
	);
	glNormal3f(N.x, N.y, N.z);
	glTexCoord2d(0.53f, 0.56f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.93f, 0.56f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.73f, 0.9f); glVertex3f(0.0f, 1.5f, 0.0f);

	glEnd();
}


glm::vec3 CScene7::CalculateQuadNormalVector(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4)
{
	/*
		   v4      v3
			+------+
			|      |
			|      |
			+------+
		   v1      v2
	*/

	glm::vec3 A, B;
	A.x = v2.x - v1.x;
	A.y = v2.y - v1.y;
	A.z = v2.z - v1.z;

	B.x = v4.x - v1.x;
	B.y = v4.y - v1.y;
	B.z = v4.z - v1.z;

	// Calcula o Cross Product
	glm::vec3 normal;
	normal.x = A.y * B.z - A.z * B.y;
	normal.y = A.z * B.x - A.x * B.z;
	normal.z = A.x * B.y - A.y * B.x;

	// Calcula a magnitude do vetor normal
	double magnitude = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	// Normaliza o vetor normal
	glm::vec3 normalizedVector;
	normalizedVector.x = (normal.x / magnitude);
	normalizedVector.y = (normal.y / magnitude);
	normalizedVector.z = (normal.z / magnitude);

	return normalizedVector;
}



glm::vec3 CScene7::CalculateTriangleNormalVector(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	/*
			   v3
			   /\
			  /  \
			 /    \
			/      \
			+------+
		   v1      v2
	*/

	glm::vec3 A, B;
	A.x = v2.x - v1.x;
	A.y = v2.y - v1.y;
	A.z = v2.z - v1.z;

	B.x = v3.x - v1.x;
	B.y = v3.y - v1.y;
	B.z = v3.z - v1.z;

	// Calcula o Cross Product
	glm::vec3 normal;
	normal.x = A.y * B.z - A.z * B.y;
	normal.y = A.z * B.x - A.x * B.z;
	normal.z = A.x * B.y - A.y * B.x;

	// Calcula a magnitude do vetor normal
	double magnitude = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	// Normaliza o vetor normal
	glm::vec3 normalizedVector;
	normalizedVector.x = (normal.x / magnitude);
	normalizedVector.y = (normal.y / magnitude);
	normalizedVector.z = (normal.z / magnitude);

	return normalizedVector;
}


