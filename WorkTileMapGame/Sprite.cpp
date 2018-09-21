#include "GameSystem.h"
#include "Frame.h"
#include "Sprite.h"
#include "Texture.h"
#include "ResourceManager.h"

#include<fstream>
#include <reader.h>//json 파싱

Sprite::Sprite(LPCWSTR textureFileName, LPCWSTR scriptFileName, float rotate) :_currentFrame(0), _frameTime(0.0f), _textureFileName(textureFileName), _scriptFileName(scriptFileName), _rotate(rotate)
{

}

Sprite::~Sprite() 
{
	_srcTexture = NULL;

}  

void Sprite::Init()
{

	//이미지 폭 너비 가져오기

	//리소스매니저를 이용한 로드
	
	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_textureFileName);

	//json Parsing
	{
		//파일 읽기

		std::vector<std::string> ScriptList = ResourceManager::GetInstance()->LoadScript(_scriptFileName);

		for (int i = 0; i < ScriptList.size(); i++)
		{
			std::string record = ScriptList[i];
		
			//Sinfile.getline(inputBuffer, 100);

			Json::Value root;
			Json::Reader reader;

			bool isSuccess = reader.parse(record, root);
			if (isSuccess)
			{
				std::string texture = root["texture"].asString();
				int x = root["x"].asInt();
				int y = root["y"].asInt();
				int width = root["width"].asInt();
				int height = root["height"].asInt();
				double delay = root["freamDelay"].asDouble();

				Frame * frame = new Frame();
				frame->Init(_srcTexture, x, y, width, height,_rotate,(float) delay);
				_frameList.push_back(frame);
			 }
		}

	}

	_currentFrame = 0;

	_frameTime = 0.0f;
}
int Sprite::GetWidth()
{
	return _frameList[_currentFrame]->GetWidth();
}

int Sprite::Getheight()
{
	return _frameList[_currentFrame]->GetHeight();
}


void Sprite::Init(int srcX, int srcY, int width, int height, float delay)
{

	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_textureFileName);

	{
		Frame * frame = new Frame();
		frame->Init(_srcTexture, srcX, srcY, width, height,_rotate, delay);
		_frameList.push_back(frame);
	}

	_currentFrame = 0;

	_frameTime = 0.0f;
}

void Sprite::Update(float deltaTime)
{
	_frameTime += deltaTime;
	float delay = _frameList[_currentFrame]->GetFrameDelay();
	if (_frameList[_currentFrame]->GetFrameDelay() <= _frameTime)
	{
		_frameTime = 0.0f;
		
		_currentFrame = (_currentFrame + 1) % _frameList.size();
	}

}

void Sprite::deInit()
{
	std::vector<Frame*>::iterator  it = _frameList.begin();
	for (it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame * frame = (*it);
		frame->deInit();
		delete frame;
	}
	_frameList.clear();

	_srcTexture = NULL;
}
void Sprite::render()
{
	//스프라이트 출력전 모양 조정
	//pivot  메트릭스의 계산을 돕기위해 가운데 맞춤

	if (_currentFrame < _frameList.size())
	{
		_frameList[_currentFrame]->SetPosition(_x, _y);
		_frameList[_currentFrame]->render();
	}
}


void Sprite::Release() 
{
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame * frame = (*itr);
		frame->Release();
	}
	_srcTexture->Release();
}

void Sprite::Reset() 
{
	Init();
	//_frame->Reset(direxct3Ddevice, sprite);

	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame * frame = (*itr);
		frame->Reset();
	}
}
void Sprite::setPostition(float posX, float posY)
{
	_x = posX;
	_y = posY;
}