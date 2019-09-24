#include "Input.h"



Input::Input() {
}


Input::~Input() {
}


void updateKeyAndMouseInput(bool *freeFlight, bool *culling, bool *showCullingObjects, bool * wireframe, bool *forceSingle, bool *onlyQuadCulling, Frustum* camFrustum, bool *renderOnce, duration<double, std::ratio<1, 15>> delta) {

	//KEYBOARD 
	{
		auto kb = keyboardInput->GetState();
		//SHORT COMMANDS
		{
			if (kb.Escape) {
				camera.SetCamPos(camera.GetCamOriginalPos());
				camera.SetYawAndPitch(0, 0);
				camera.SetCamTarget(camera.GetCamOriginalTarget());
			}
			if (kb.F1) {
				camera.SetCamPos({ float(-g_heightmap.imageWidth / 2),3.0f,float(+g_heightmap.imageHeight / 2),0.0f });

				float hyp = sqrt((pow(g_heightmap.imageWidth / 2, 2) + pow(g_heightmap.imageHeight / 2, 2)));

				float angel = ((g_heightmap.imageWidth / 2) / hyp);

				camera.SetYawAndPitch(XM_PI*angel, 0);
			}
			if (kb.F2) {
				camera.SetCamPos({ float(+g_heightmap.imageWidth / 2),3.0f,float(+g_heightmap.imageHeight / 2),0.0f });

				float hyp = sqrt((pow(g_heightmap.imageWidth / 2, 2) + pow(g_heightmap.imageHeight / 2, 2)));

				float angel = ((g_heightmap.imageWidth / 2) / hyp) + 0.5f;
				//angel = 0.0f;
				camera.SetYawAndPitch(XM_PI*angel, 0);
			}
			if (kb.F3) {
				camera.SetCamPos({ float(+g_heightmap.imageWidth / 2),3.0f,float(-g_heightmap.imageHeight / 2),0.0f });

				float hyp = sqrt((pow(g_heightmap.imageWidth / 2, 2) + pow(g_heightmap.imageHeight / 2, 2)));

				float angel = ((g_heightmap.imageWidth / 2) / hyp) + 1.0f;

				camera.SetYawAndPitch(XM_PI*angel, 0);
			}
			if (kb.F4) {
				camera.SetCamPos({ float(-g_heightmap.imageWidth / 2),3.0f,float(-g_heightmap.imageHeight / 2),0.0f });

				float hyp = sqrt((pow(g_heightmap.imageWidth / 2, 2) + pow(g_heightmap.imageHeight / 2, 2)));

				float angel = ((g_heightmap.imageWidth / 2) / hyp) + 1.5;

				camera.SetYawAndPitch(XM_PI*angel, 0);
			}

			//TOGGLE KEYS
			if (!keyReleased) {
				if (kb.O) {

				} else if (kb.R) {

				} else if (kb.P) {

				} else if (kb.U) {

				} else if (kb.Y) {

				} else if (kb.H) {

				} else  if (kb.J) {

				} else {
					keyReleased = true;
				}

			}
			if (keyReleased) {
				if (kb.O) {
					if (*freeFlight == true)
						*freeFlight = false;
					else
						*freeFlight = true;

					keyReleased = false;
				}
				if (kb.R) {
					camera.AddYaw(XM_PI*0.1f);
					keyReleased = false;
				}
				if (kb.P) {
					if (*culling == true) {
						*culling = false;
						*showCullingObjects = false;
						*onlyQuadCulling = false;
					} else
						*culling = true;
					keyReleased = false;
				}
				if (kb.U) {
					if (*culling == true) {
						if (*showCullingObjects == true)
							* showCullingObjects = false;

						else
							* showCullingObjects = true;
					}
					keyReleased = false;
				}
				if (kb.Y) {
					if (*forceSingle == true) {
						*forceSingle = false;
					} else {
						*forceSingle = true;
					}
					keyReleased = false;
				}
				if (kb.H) {
					if (*wireframe == true) {
						*wireframe = false;
					} else {
						*wireframe = true;
					}
					keyReleased = false;
				}
				if (kb.J) {
					if (*culling == true) {
						if (*onlyQuadCulling == true) {
							*onlyQuadCulling = false;
						} else {
							*onlyQuadCulling = true;
						}
					}
					keyReleased = false;
				}

				//WIRE FRAME CHECK ?

			}
		}

		//MOUSE INPUT PRESS LEFTCLICK TO ANGEL
		auto mouse = mouseInput->GetState();

		if (mouse.positionMode == Mouse::MODE_RELATIVE) {
			//MOUSE RELATIVE CONTROL
			float deltaPos[3] = { float(-mouse.x)* ROTATION_GAIN, float(mouse.y)* ROTATION_GAIN, 0.0f };

			camera.UpdateYawAndPitch(deltaPos[0], deltaPos[1]);
		}

		mouseInput->SetMode(mouse.leftButton ? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE);

		Vector3 moveInDepthCameraClass = Vector3::Zero;
		Vector3 deltaChange = Vector3::Zero;
		bool run = false;

		//UPDATE VECTOR

		if (kb.LeftShift) {
			run = true;
		}

		//pineapple in a green pie
		if (kb.W) {//FORWARD IN

			if (*freeFlight) {
				moveInDepthCameraClass += camera.GetCameraNormal();
			} else {
				moveInDepthCameraClass += camera.GetCamForward();
			}

		}
		if (kb.S) { //BACK
			if (*freeFlight) {
				moveInDepthCameraClass -= camera.GetCameraNormal();
			} else {
				moveInDepthCameraClass -= camera.GetCamForward();
			}

		}
		if (kb.D) { //RIGHT
			deltaChange.x += 1.0f;
		}
		if (kb.A) { //LEFT
			deltaChange.x -= 1.0f;
		}
		if (kb.Q) { //UP
			if (*freeFlight)
				deltaChange.y += 1.0f;
		}
		if (kb.E) { //DOWN
			if (*freeFlight)
				deltaChange.y -= 1.0f;
		}

		/*
		Keys for different rendering options
		*/

		if (kb.F6 && !key_down) {
			blurFilter = !blurFilter;
			key_down = true;
		}

		if (kb.F7 && !key_down) {
			renderMode++;
			renderMode %= 8;
			key_down = true;
		}

		if (kb.F8 && !key_down) {
			currentLight++;
			currentLight %= 3;

			*renderOnce = true;

			key_down = true;
		}

		if (kb.F9 && !key_down) {
			if (renderOpt & RENDER_WIREFRAME)
				renderOpt &= ~RENDER_WIREFRAME;
			else
				renderOpt |= RENDER_WIREFRAME;

			SetRasterizerState();

			key_down = true;
		}

		if (kb.F10 && !key_down) {
			if (renderOpt & RENDER_MULTI_VIEWPORT)
				renderOpt &= ~RENDER_MULTI_VIEWPORT;
			else
				renderOpt |= RENDER_MULTI_VIEWPORT;

			key_down = true;
		}


		//UPDATE CAMERA
		{
			deltaChange = XMVector3Normalize(deltaChange);
			//ROTATION OF CAMERA
			deltaChange = deltaChange.x*camera.GetCamRight() + deltaChange.y*camera.GetCamUp();
			deltaChange += moveInDepthCameraClass;

			deltaChange = deltaChange;
			camera.UpdateCamera({ deltaChange.x,deltaChange.y,deltaChange.z }, run, float(delta.count()));

			//Walking on terrain
			if (!*freeFlight) {
				Vector4 CameraPos = camera.GetCamPos();
				Vector4 CameraForward = camera.GetCamForward();

				//TEST byte ordningen så det liknar en graf.

				//2 mätpunkter 1 på cameran samt en framför

				XMINT2 nRoundedPos;
				nRoundedPos.x = CameraPos.x;
				nRoundedPos.y = CameraPos.z;

				XMINT2 n2RoundedPos;
				n2RoundedPos.x = CameraPos.x + CameraForward.x;
				n2RoundedPos.y = CameraPos.z + CameraForward.z;

				//avrundar till närmsta heltal
				if (nRoundedPos.x < 0) {
					if (float(nRoundedPos.x) - 0.5f > CameraPos.x) nRoundedPos.x--;
				} else {
					if (float(nRoundedPos.x) + 0.5f < CameraPos.x) nRoundedPos.x++;
				}
				if (nRoundedPos.y < 0) {
					if (float(nRoundedPos.y) - 0.5f > CameraPos.z) nRoundedPos.y--;
				} else {
					if (float(nRoundedPos.y) + 0.5f < CameraPos.z) nRoundedPos.y++;
				}
				if (n2RoundedPos.x < 0) {
					if (float(n2RoundedPos.x) - 0.5f > CameraPos.x) n2RoundedPos.x--;
				} else {
					if (float(n2RoundedPos.x) + 0.5f < CameraPos.x) n2RoundedPos.x++;
				}
				if (n2RoundedPos.y < 0) {
					if (float(n2RoundedPos.y) - 0.5f > CameraPos.z) n2RoundedPos.y--;
				} else {
					if (float(n2RoundedPos.y) + 0.5f < CameraPos.z) n2RoundedPos.y++;
				}

				nRoundedPos.x += g_heightmap.imageWidth / 2;
				nRoundedPos.y += g_heightmap.imageHeight / 2;

				n2RoundedPos.x += g_heightmap.imageWidth / 2;
				n2RoundedPos.y += g_heightmap.imageHeight / 2;

				//Avrundar så ingen ogiltig arrayplats nåss
				if (nRoundedPos.x < 0) nRoundedPos.x = 0;
				if (nRoundedPos.x >= g_heightmap.imageWidth) nRoundedPos.x = g_heightmap.imageWidth - 1;

				if (n2RoundedPos.x < 0) n2RoundedPos.x = 0;
				if (n2RoundedPos.x >= g_heightmap.imageWidth) n2RoundedPos.x = g_heightmap.imageWidth - 1;

				if (nRoundedPos.y < 0) nRoundedPos.y = 0;
				if (nRoundedPos.y >= g_heightmap.imageHeight) nRoundedPos.y = g_heightmap.imageHeight - 1;

				if (n2RoundedPos.y < 0) n2RoundedPos.y = 0;
				if (n2RoundedPos.y >= g_heightmap.imageHeight) n2RoundedPos.y = g_heightmap.imageHeight - 1;


				int index = (nRoundedPos.y * g_heightmap.imageWidth) + nRoundedPos.x;

				int index2 = (n2RoundedPos.y * g_heightmap.imageWidth) + n2RoundedPos.x;

				/*float newHeight = (g_heightmap.verticesPos[index].y  + WALKING_HEIGHT);*/

				float newHeight = ((g_heightmap.verticesPos[index].y + g_heightmap.verticesPos[index2].y) / 2 + WALKING_HEIGHT);

				//ställer pitch, yaw, ny höjd 
				camera.SetCameraHeight(newHeight);
			}

			camFrustum->calculateFrustum(FOV, W_WIDTH, W_HEIGHT, 2.5f);

			Vector4 temp = camera.GetCameraNormal()* (camFrustum->frustumFarDist - camFrustum->frustumNearDist);


			//reset
			objectsFromFrustum = 0;

			objectsCulledFromQuad = 0;

			int capacity = elementsAmount;

			if (*culling == true) {

				//rough culling the quadtree
				int testing = camFrustum->isQuadInside(&theObjectTree, objectsCulledFromQuad, elementsIndexQuadCulling, capacity);

				//culling individuel objects

				/*for (int i = 0; i < elementsAmount; i++)
				{

				if (true)
				{


				if (camFrustum->sphereInFrustum(Vector3 {copies[i].x,copies[i].y,copies[i].z},50.0f) > 0)
				{
				elementsIndexFrustumCulling[objectsFromFrustum] = copies[i].index;
				objectsFromFrustum++;
				}
				}
				}
				*/
				/*cullingfrustum =*/
				//COMBINE
				for (int i = 0; i < objectsCulledFromQuad; i++) {

					if (true) {
						if (camFrustum->sphereInFrustum(Vector3{ copies[elementsIndexQuadCulling[i]].x,
							copies[elementsIndexQuadCulling[i]].y,copies[elementsIndexQuadCulling[i]].z }, 25.0f) > 0) {
							elementsIndexFrustumCulling[objectsFromFrustum] = copies[elementsIndexQuadCulling[i]].index;
							objectsFromFrustum++;
						}
					}
				}
			}
		}
	}
}

