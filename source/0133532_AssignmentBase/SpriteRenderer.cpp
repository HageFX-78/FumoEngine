#include "SpriteRenderer.h"
#include "ResourceAllocator.h"
#include "Texture.h"


namespace FumoEngine
{
	SpriteRenderer::SpriteRenderer(GameObject* go
		, std::string spritePath
		, Vector4 dColor
		, Vector2 dPivot
		, Vector2 dSize
	) : BaseComponent(go)
	{
		allowMultiple = false;
		texture = ResourceAllocator::allocateResource<Texture>(spritePath);

		localTransform = go->getComponent<TransformComponent>();
		setColor(dColor.x, dColor.y, dColor.z);
		setOpacity(dColor.w);

		setPivot(dPivot.x, dPivot.y);
		setSize(dSize.x, dSize.y);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		ResourceAllocator::releaseResource<Texture>(texture);
	}

	void SpriteRenderer::render()
	{
		glPushMatrix();

		//Offset by local size and height so different sprite renderers have different local w and h
		float scaledTextWidth = texture->getTextureWidth() * 0.5f * w;
		float scaledTextHeight = texture->getTextureHeight() * 0.5f * h;

		// Translation
		Vector3 translationVector(localTransform->getXPosition(), localTransform->getYPosition(), 0.0f);
		Matrix4 translationMatrix = Matrix4::translate(translationVector);

		// Rotation
		float pivotX = 2.0f * pivotPoint.x - 1.0f;//Scale the default -1.0 to 1.0 pivot till 0.0 to 1,0 based on requirement
		float pivotY = 2.0f * pivotPoint.y - 1.0f;

		Vector3 pivotOffset(pivotX * scaledTextWidth, pivotY * scaledTextHeight, 1.0f);
		Matrix4 pivotTranslate = Matrix4::translate(pivotOffset);
		Matrix4 pivotRotate = Matrix4::rotate(localTransform->getRotation(), Vector3(0.0f, 0.0f, 1.0f));
		Matrix4 pivotTranslateBack = Matrix4::translate(-pivotOffset);
		Matrix4 rotationMatrix = pivotTranslate * pivotRotate * pivotTranslateBack;

		// Scale
		Vector3 scaleVector(localTransform->getXScale(), localTransform->getYScale(), 1.0f);
		Matrix4 scaleMatrix = Matrix4::scale(scaleVector);


		Matrix4 allMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		glMultMatrixf(allMatrix.data);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);

		texture->bind();

		glBegin(GL_QUADS);
		glColor4f(r, g, b, a);


		glTexCoord2f(0.0f, 1.0f); glVertex3f(-scaledTextWidth, scaledTextHeight, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-scaledTextWidth, -scaledTextHeight, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(scaledTextWidth, -scaledTextHeight, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(scaledTextWidth, scaledTextHeight, 0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		glPopMatrix();
	}

	void SpriteRenderer::setColor(float nR, float nG, float nB)
	{
		r = nR / 255;
		g = nG / 255;
		b = nB / 255;
	}

	void SpriteRenderer::setColor(Vector3 color)
	{
		r = color.x;
		g = color.y;
		b = color.z;
	}

	Vector3 SpriteRenderer::getColor()
	{
		return Vector3(r, g, b);
	}

	void SpriteRenderer::setOpacity(float nA)
	{
		a = nA;
	}

	float SpriteRenderer::getOpacity()
	{
		return a;
	}

	void SpriteRenderer::setSize(float nW, float nH)
	{
		w = nW;
		h = nH;
	}

	void SpriteRenderer::setSize(Vector2 size)
	{
		w = size.x;
		h = size.y;
	}

	Vector2 SpriteRenderer::getSize()
	{
		return Vector2(w, h);
	}

	void SpriteRenderer::setPivot(float x, float y)
	{
		pivotPoint = Vector3(x, y, 0);
	}

	void SpriteRenderer::setPivot(Vector2 pivot)
	{
		pivotPoint = Vector3(pivot.x, pivot.y, 0);
	}

	Vector2 SpriteRenderer::getPivot()
	{
		return Vector2(pivotPoint.x, pivotPoint.y);
	}

	void SpriteRenderer::setSprite(std::string path)
	{
		ResourceAllocator::releaseResource<Texture>(texture);
		texture = ResourceAllocator::allocateResource<Texture>(path);
	}
}

