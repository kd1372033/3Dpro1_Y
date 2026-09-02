#pragma once

class Player;

class Cloud : public KdGameObject
{
public:

	Cloud() {}
	~Cloud()			override {}

	void Update()		override;
	void DrawEffect()	override;
	void Init()			override;

	void SetPlayer(const std::shared_ptr<Player>& _player)
	{
		m_wpPlayer = _player;
	}

private:

	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;

	std::weak_ptr<Player> m_wpPlayer;

};