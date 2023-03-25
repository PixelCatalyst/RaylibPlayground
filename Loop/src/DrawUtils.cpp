#include "DrawUtils.h"

#include <rlgl.h>

void DrawUtils::drawCentered(const DrawItem& drawItem)
{
    const Vector2 itemSize = drawItem.size();
    const Vector2 renderSize{
            static_cast<float>(GetRenderWidth()),
            static_cast<float>(GetRenderHeight())
    };
    rlPushMatrix();
    rlTranslatef((renderSize.x - itemSize.x) / 2.0f, (renderSize.y - itemSize.y) / 2.0f, 0);
    drawItem.draw();
    rlPopMatrix();
}

Vector2 DrawItem::size() const
{
    return Vector2{0.0f, 0.0f};
}
