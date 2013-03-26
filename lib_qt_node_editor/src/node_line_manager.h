#ifndef __NODE_LINE_MANAGER_H__
#define __NODE_LINE_MANAGER_H__


#include "use_spec.h"
#include <QPointF>
#include <QList>


class NodeLine;
class NodePortIn;
class NodePortOut;

class NodeLineManager
{
public:
	NodeLineManager(NodePortOut* pNodePortSrc);
	~NodeLineManager();
	bool addNodeLine(NodeLine* pNodeLine);
	NodeLine* removeNodeLine(NodePortIn* pPortIn);
	bool isConnect();

private:
	NodeLine* _getNodeLineFromPortIn(NodePortIn* pPortIn);

private:
	QList<NodeLine*> _listNodeLines;
	NodePortOut* _pNodePortSrc;

};

#endif /* __NODE_LINE_MANAGER_H__ */
