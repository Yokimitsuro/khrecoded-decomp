extern unsigned int DrawTextAnchored();

void DrawShadowedAnchoredText_020bfd34
               (void *renderer,int x,int y,int color,unsigned int anchor,void *text)

{
  DrawTextAnchored(renderer,x + 1,y + 1,color + 1,anchor,text);
  DrawTextAnchored(renderer,x,y,color,anchor,text);
  return;
}
