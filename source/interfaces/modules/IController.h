#ifndef ICONTROLLER_H
#define ICONTROLLER_H

class IController
{
public:
	virtual ~IController() {}
    virtual void Process() = 0;
};

#endif
