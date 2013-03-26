#include "node_line_manager.h"
#include "node_line.h"


NodeLineManager::NodeLineManager(NodePortOut* pNodePortSrc)
{
	_pNodePortSrc = pNodePortSrc;
}


NodeLineManager::~NodeLineManager()
{
}


bool NodeLineManager::addNodeLine(NodeLine* pNodeLine)
{
	if (pNodeLine == NULL) {
		return false;
	}

	/* ä˘Ç…ìoò^çœÇ›ÇÃ NodePortOut ÇÃèÍçáÇÕìoò^ÇµÇ»Ç¢ */
	int nSize = _listNodeLines.size();
	for (int i = 0; i < nSize; i++) {
		if (_listNodeLines[i]->m_pNodeDstPort == pNodeLine->m_pNodeDstPort) {
			return false;
		}
	}

	_listNodeLines.push_back(pNodeLine);
	return true;
}


NodeLine* NodeLineManager::_getNodeLineFromPortIn(NodePortIn* pPortIn)
{
	NodeLine* pNodeLine = NULL;

	int nSize = _listNodeLines.size();
	for (int i = 0; i < nSize; i++) {
		if (_listNodeLines[i]->m_pNodeDstPort == pPortIn) {
			pNodeLine = _listNodeLines[i];
			break;
		}
	}

	return pNodeLine;
}


NodeLine* NodeLineManager::removeNodeLine(NodePortIn* pPortIn)
{
	NodeLine* pNodeLine = _getNodeLineFromPortIn(pPortIn);
	if (pNodeLine == NULL) {
		return NULL;
	}

	pNodeLine->setNodeDstPort(NULL);
	int nIndex = _listNodeLines.indexOf(pNodeLine);
	_listNodeLines.removeAt(nIndex);

	return pNodeLine;
}


bool NodeLineManager::isConnect()
{
	int nSize = _listNodeLines.size();
	
	if (nSize > 0) {
		return true;
	} else {
		return false;
	}
}
