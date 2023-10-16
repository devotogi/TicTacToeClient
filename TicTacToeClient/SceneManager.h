#pragma once
class Wnd;
class Scene;

class SceneManager
{
private:
	static SceneManager* _instance;
	map<int, Scene*> _scenes;
	int	_nowScene = 0;

	class TCPNetwork* _tcpNetwork;
	class UDPNetwork* _udpNetwork;

public:
	static SceneManager* GetInstance() 
	{
		if (_instance == nullptr)
			_instance = new SceneManager();

		return _instance;
	}
	
	Scene* GetScene();
	void Update(Wnd* wnd);
	void Render(Wnd* wnd);
	void Add(int sceneType, Scene* scene);
	void ChangeScene(SceneType type, Wnd* wnd);

	void MouseClickEvent(int x, int y);
	void NetworkSetting(TCPNetwork* tcp, UDPNetwork* udp) { _tcpNetwork = tcp, _udpNetwork = udp; }

	TCPNetwork* GetTCP() { return _tcpNetwork; }
	UDPNetwork* GetUDP() { return _udpNetwork; }
};

