#ifndef __NODEGRAPHICSVIEW_H__
#define __NODEGRAPHICSVIEW_H__

#include <QGraphicsView>

class NodeDiagramScene;

class NodeGraphicsView : public QGraphicsView
{
public:
	NodeGraphicsView(QWidget* parent = 0);
	~NodeGraphicsView();
	int init();
	void fin();

protected: /* override */
	void dragEnterEvent(QDragEnterEvent* event);
	void dropEvent(QDropEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void NodeGraphicsView::wheelEvent(QWheelEvent* event);

private:
	void _putNodeItem(const QString& fName, const QPoint& pos);
	void _translateSceneItem(int nMouseX, int nMouseY);

public:
	NodeDiagramScene* m_pScene;

private:
	bool _isMouseTranslate;
	int _nPressMouseX;
	int _nPressMouseY;

};

#endif /* __NODEGRAPHICSVIEW_H__ */
