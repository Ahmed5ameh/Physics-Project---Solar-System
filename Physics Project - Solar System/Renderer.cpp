#include "Renderer.h"
#include <iterator>

using namespace std;

void Renderer::AddDrawable(Drawable* drawable)
{
	drawables.push_back(drawable);
}

void Renderer::Render(RenderWindow* window)
{
	list<Drawable*>::iterator it;
	window->clear();
	for (it = drawables.begin(); it != drawables.end(); it++)
	{
		window->draw(**it);
	}
	window->display();

}

void Renderer::ClearDrawables()
{
	drawables.clear();
}
