#ifndef TEXTURE_H
#define TEXTURE_H

#include <QObject>
#include "qopenglfunctions_selector.h"

class Texture : public QObject
{
	Q_OBJECT
public:
	explicit Texture(QOPENGLFUNCTIONS_CLASSNAME &, int, QObject *parent = 0);
	Texture(const Texture &);

	int id() { return m_id; }
	void bind();

private:
	int m_id;
	QOPENGLFUNCTIONS_CLASSNAME &f;
};

#endif // TEXTURE_H
