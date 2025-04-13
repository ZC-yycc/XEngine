#include "XEngine.h"
#include "ThirdPartyLib/GL/glew.h"
#include "ThirdPartyLib/GLFW/glfw3.h"
#include "XObject.h"
#include "SceneManager.h"
#include "XWorld.h"
#include "XGUIBase.h"

XEngine* XEngine::pEngine_ = nullptr;

std::shared_ptr<XObject> findObjectWithName(const std::wstring& name) {
	return XCurrentWorld->findObjectWithName(name);
}

std::vector<std::shared_ptr<XObject>> findObjectsWithName(const std::wstring& name)
{
	return  XCurrentWorld->findObjectsWithName(name);
}

void gameExit()
{
	XEngine::exitGame();
}

void destroy(std::shared_ptr<XObject> destroy_obj)
{
	XCurrentWorld->removeObject(destroy_obj);
}

void addNewGUI(std::shared_ptr<XGUIBase> pNewGUI)
{
	XCurrentWorld->addGUI(pNewGUI);
}

void XEngine::drawCircle(const Vector2& center, float radius, int segments)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(center.x_, center.y_);  // Բ��
	for (int i = 0; i <= segments; i++) {
		float angle = i * 2.0f * XPI / segments;
		glVertex2f(center.x_ + radius * cos(angle), center.y_ + radius * sin(angle));
	}
	glEnd();
}

void XEngine::drawLine(const Vector2& begin, const Vector2& end)
{
	XEngine::getInstance()->line_.draw(begin, end);
}

void XEngine::drawBox(const Vector2& center, const Vector2& w_h) {
	// �����ĸ��ǵ�
	Vector2 topLeft(center.x_ - w_h.x_ / 2, center.y_ + w_h.y_ / 2);
	Vector2 topRight(center.x_ + w_h.x_ / 2, center.y_ + w_h.y_ / 2);
	Vector2 bottomRight(center.x_ + w_h.x_ / 2, center.y_ - w_h.y_ / 2);
	Vector2 bottomLeft(center.x_ - w_h.x_ / 2, center.y_ - w_h.y_ / 2);

	// ����������
	drawLine(topLeft, topRight);      // �ϱ�
	drawLine(topRight, bottomRight);   // �ұ�
	drawLine(bottomRight, bottomLeft); // �±�
	drawLine(bottomLeft, topLeft);     // ���
}

void XEngine::drawCircle(const Vector2& center, int radius, int segments)
{
	const double angleStep = 2 * XPI / segments;  // ÿ�νǶ�����
	double prevX = center.x_ + radius;  // ��ʼ�㣨�Ҳඥ�㣩
	double prevY = center.y_;

	for (int i = 1; i <= segments; i++) {
		double theta = angleStep * i;  // ��ǰ�Ƕ�
		double x = center.x_ + radius * cos(theta);
		double y = center.y_ + radius * sin(theta);
		drawLine(Vector2(prevX, prevY), Vector2(x, y));  // �����߶�
		prevX = x;
		prevY = y;
	}
}