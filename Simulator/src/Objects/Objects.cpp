#include "Objects.h"

Model::Model() {
}

Model::~Model() {
	vb->unBind();
	delete(vb);
	ib->unBind();
	delete(ib);
	va->unBind();
	delete(va);
}