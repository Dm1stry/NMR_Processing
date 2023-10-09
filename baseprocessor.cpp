#include "baseprocessor.h"

BaseProcessor::BaseProcessor(QObject * parent /*= nullptr*/)
  : QObject(parent)
{}

void BaseProcessor::clearData()
{
	this->updateData({});
}

BaseProcessor::~BaseProcessor()
{}