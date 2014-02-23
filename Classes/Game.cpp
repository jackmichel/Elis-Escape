#include "Game.h"
#include "Constants.h"


USING_NS_CC;

CCScene* Game::scene() {
    CCScene *sc = CCScene::create();
    sc->setTag(TAG_GAME_SCENE);
    Game *g = Game::create();
    sc->addChild(g, 0, TAG_GAME_LAYER);

    return sc;
}

bool Game::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    // Get the size of the screen
    CCSize windowSize = CCDirector::sharedDirector()->getVisibleSize();

    // create a Tiled TMX map
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("lvl1-1.tmx");
    this->addChild(_tileMap, 0);

    // Set the bounds for panning
    CCRect bounds = CCRectMake(-(windowSize.width / 2), -(windowSize.height / 2), _tileMap->getMapSize().width - 80, _tileMap->getMapSize().height - 145);
    this->setPosition(ccp(0,-windowSize.height));

    // The following block of variable declarations are for panning and zooming
    _maxScale = 1.0f;
    _minScale = 1.0f;
    _touches = CCArray::createWithCapacity(10);
    _touches->retain();
    _panBoundsRect = bounds;
    _touchDistance = 0.0F;
    _maxTouchDistanceToClick = 315.0f;
    _mode = kCCLayerPanZoomModeSheet;
    _minSpeed = 100.0f;
    _maxSpeed = 1000.0f;
    _topFrameMargin = 100.0f;
    _bottomFrameMargin = 100.0f;
    _leftFrameMargin = 100.0f;
    _rightFrameMargin = 100.0f;
    _rubberEffectRatio = 0.0f;
    _rubberEffectRecoveryTime = 0.2f;
    _rubberEffectRecovering = false;
    _rubberEffectZooming = false;
    // End Block

    this->setTouchEnabled(true);

    return true;
}


// The following methods are all related to panning and zooming, only to be edited when absolutely necessary
void Game::setMaxScale(float maxScale)
{
    _maxScale = maxScale;
    this->setScale(MIN(this->getScale(), _maxScale));
}

float Game::maxScale()
{
    return _maxScale;
}

void Game::setMinScale(float minScale)
{
    _minScale = minScale;
    this->setScale(MAX(this->getScale(), minScale));
}

float Game::minScale()
{
    return _minScale;
}

void Game::setRubberEffectRatio(float rubberEffectRatio)
{
    _rubberEffectRatio = rubberEffectRatio;

    // Avoid turning rubber effect On in frame mode.
    if (_mode == kCCLayerPanZoomModeFrame)
    {
        CCLOGERROR("CCLayerPanZoom#setRubberEffectRatio: rubber effect is not supported in frame mode.");
        _rubberEffectRatio = 0.0f;
    }

}

float Game::rubberEffectRatio()
{
    return _rubberEffectRatio;
}


Game* Game::layer()
{
    // 'layer' is an autorelease object
    Game *layer = Game::create();

    // return the scene
    return layer;
}

void Game::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch *pTouch;
    CCSetIterator setIter;
    for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter)
    {
        pTouch = (CCTouch *)(*setIter);
        _touches->addObject(pTouch);
    }


    if (_touches->count() == 1)
    {
        _touchMoveBegan = false;
        time_t seconds;

        seconds = time (NULL);
        _singleTouchTimestamp = seconds/60;
    }
    else
        _singleTouchTimestamp = INFINITY;
}

void Game::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    bool multitouch = _touches->count() > 1;
    if (multitouch)
    {
        // Get the two first touches
        CCTouch *touch1 = (CCTouch*)_touches->objectAtIndex(0);
        CCTouch *touch2 = (CCTouch*)_touches->objectAtIndex(1);
        // Get current and previous positions of the touches
        CCPoint curPosTouch1 = CCDirector::sharedDirector()->convertToGL(touch1->getLocationInView());
        CCPoint curPosTouch2 = CCDirector::sharedDirector()->convertToGL(touch2->getLocationInView());

        CCPoint prevPosTouch1 = CCDirector::sharedDirector()->convertToGL(touch1->getPreviousLocationInView());
        CCPoint prevPosTouch2 = CCDirector::sharedDirector()->convertToGL(touch2->getPreviousLocationInView());


        // Calculate current and previous positions of the layer relative the anchor point
        CCPoint curPosLayer = ccpMidpoint(curPosTouch1, curPosTouch2);
        CCPoint prevPosLayer = ccpMidpoint(prevPosTouch1, prevPosTouch2);

        // Calculate new scale
        float prevScale = this->getScale();


        float curScale = this->getScale() * ccpDistance(curPosTouch1, curPosTouch2) / ccpDistance(prevPosTouch1, prevPosTouch2);

        this->setScale( curScale);
        // Avoid scaling out from panBoundsRect when Rubber Effect is OFF.
        if (!_rubberEffectRatio)
        {
            this->setScale( MAX(this->getScale(), this->minPossibleScale()));
        }
        // If scale was changed -> set new scale and fix position with new scale
        if (this->getScale() != prevScale)
        {
            if (_rubberEffectRatio)
            {
                _rubberEffectZooming = true;
            }
            CCPoint realCurPosLayer = this->convertToNodeSpace(curPosLayer);
            float deltaX = (realCurPosLayer.x - this->getAnchorPoint().x * this->getContentSize().width) * (this->getScale() - prevScale);
            float deltaY = (realCurPosLayer.y - this->getAnchorPoint().y * this->getContentSize().height) * (this->getScale() - prevScale);
            this->setPosition(ccp(this->getPosition().x - deltaX, this->getPosition().y - deltaY));
            _rubberEffectZooming = false;
        }
        // If current and previous position of the multitouch's center aren't equal -> change position of the layer
        if (!prevPosLayer.equals(curPosLayer))
        {
            this->setPosition(ccp(this->getPosition().x + curPosLayer.x - prevPosLayer.x,
                this->getPosition().y + curPosLayer.y - prevPosLayer.y));
        }
        // Don't click with multitouch
        _touchDistance = INFINITY;
    }
    else
    {
        // Get the single touch and it's previous & current position.
        CCTouch *touch = (CCTouch*)_touches->objectAtIndex(0);
        CCPoint curTouchPosition = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        CCPoint prevTouchPosition = CCDirector::sharedDirector()->convertToGL(touch->getPreviousLocationInView());

        // Always scroll in sheet mode.
        if (_mode == kCCLayerPanZoomModeSheet)
        {
            // Set new position of the layer.
            this->setPosition(ccp(this->getPosition().x + curTouchPosition.x - prevTouchPosition.x,
                this->getPosition().y + curTouchPosition.y - prevTouchPosition.y));
        }

        // Accumulate touch distance for all modes.
        _touchDistance += ccpDistance(curTouchPosition, prevTouchPosition);

        // Inform delegate about starting updating touch position, if click isn't possible.
        if (_mode == kCCLayerPanZoomModeFrame)
        {
            if (_touchDistance > _maxTouchDistanceToClick && !_touchMoveBegan)
            {
                //ToDo add delegate here
                //[self.delegate layerPanZoom: self
                //  touchMoveBeganAtPosition: [self convertToNodeSpace: prevTouchPosition]];
                _touchMoveBegan = true;
            }
        }
    }
}

void Game::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    _singleTouchTimestamp = INFINITY;

    // Process click event in single touch.
    //ToDo add delegate
    if (  (_touchDistance < _maxTouchDistanceToClick) /*&& (self.delegate) */
        && (_touches->count() == 1))
    {
        CCTouch *touch = (CCTouch*)_touches->objectAtIndex(0);
        CCPoint curPos = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        //ToDo add delegate
        /*[self.delegate layerPanZoom: self
        clickedAtPoint: [self convertToNodeSpace: curPos]
        tapCount: [touch tapCount]];*/
    }

    CCTouch *pTouch;
    CCSetIterator setIter;
    for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter)
    {
        pTouch = (CCTouch *)(*setIter);
        _touches->removeObject(pTouch);
    }

    if (_touches->count() == 0)
    {
        _touchDistance = 0.0f;
    }

    if (!_touches->count() && !_rubberEffectRecovering)
    {
        this->recoverPositionAndScale();
    }
}

void Game::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){

    CCTouch *pTouch;
    CCSetIterator setIter;
    for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter)
    {
        pTouch = (CCTouch *)(*setIter);
        _touches->removeObject(pTouch);
    }

    if (_touches->count() == 0)
    {
        _touchDistance = 0.0f;
    }
}


// Updates position in frame mode.
void  Game::update(float dt){
    // Only for frame mode with one touch.
    if ( _mode == kCCLayerPanZoomModeFrame && _touches->count() == 1 )
    {
        // Do not update position if click is still possible.
        if (_touchDistance <= _maxTouchDistanceToClick)
            return;

        // Do not update position if pinch is still possible.
        time_t seconds;

        seconds = time (NULL);
        seconds /= 60;
        if (seconds - _singleTouchTimestamp < kCCLayerPanZoomMultitouchGesturesDetectionDelay)
            return;

        // Otherwise - update touch position. Get current position of touch.
        CCTouch *touch = (CCTouch*)_touches->objectAtIndex(0);
        CCPoint curPos = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());

        // Scroll if finger in the scroll area near edge.
        if (this->frameEdgeWithPoint(curPos) != kCCLayerPanZoomFrameEdgeNone)
        {
            this->setPosition(ccp(this->getPosition().x + dt * this->horSpeedWithPosition( curPos),
                this->getPosition().y + dt * this->vertSpeedWithPosition(curPos)));
        }

        // Inform delegate if touch position in layer was changed due to finger or layer movement.
        CCPoint touchPositionInLayer = this->convertToNodeSpace(curPos);
        if (!_prevSingleTouchPositionInLayer.equals(touchPositionInLayer))
        {
            _prevSingleTouchPositionInLayer = touchPositionInLayer;
            //ToDo add delegate
            //[self.delegate layerPanZoom: self
            //      touchPositionUpdated: touchPositionInLayer];
        }

    }
}

void  Game::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

void  Game::onExit(){
    // CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
    CCLayer::onExit();
}
void Game::setPanBoundsRect(CCRect rect){
    _panBoundsRect = rect;
    this->setScale(this->minPossibleScale());
    this->setPosition(this->getPosition());
}

void Game::setPosition(CCPoint  position){
    CCPoint prevPosition = this->getPosition();
    //May be it wouldnot work
    CCNode::setPosition(position);

    if (!_panBoundsRect.equals(CCRectZero) && !_rubberEffectZooming)
    {
        if (_rubberEffectRatio && _mode == kCCLayerPanZoomModeSheet)
        {
            if (!_rubberEffectRecovering)
            {
                float topDistance = this->topEdgeDistance();
                float bottomDistance = this->bottomEdgeDistance();
                float leftDistance = this->leftEdgeDistance();
                float rightDistance = this->rightEdgeDistance();
                float dx = this->getPosition().x - prevPosition.x;
                float dy = this->getPosition().y - prevPosition.y;
                if (bottomDistance || topDistance)
                {
                    CCNode::setPosition(ccp(this->getPosition().x,
                        prevPosition.y + dy * _rubberEffectRatio));
                }
                if (leftDistance || rightDistance)
                {
                    CCNode::setPosition(ccp(prevPosition.x + dx * _rubberEffectRatio,
                        this->getPosition().y));
                }
            }
        }
        else
        {
            CCRect boundBox = this->boundingBox();
            if (this->getPosition().x - boundBox.size.width * this->getAnchorPoint().x > _panBoundsRect.origin.x)
            {
                CCNode::setPosition(ccp(boundBox.size.width * this->getAnchorPoint().x + _panBoundsRect.origin.x,
                    this->getPosition().y));
            }
            if (this->getPosition().y - boundBox.size.height * this->getAnchorPoint().y > _panBoundsRect.origin.y)
            {
                CCNode::setPosition(ccp(this->getPosition().x, boundBox.size.height * this->getAnchorPoint().y +
                    _panBoundsRect.origin.y));
            }
            if (this->getPosition().x + boundBox.size.width * (1 - this->getAnchorPoint().x) < _panBoundsRect.size.width +
                _panBoundsRect.origin.x)
            {
                CCNode::setPosition(ccp(_panBoundsRect.size.width + _panBoundsRect.origin.x -
                    boundBox.size.width * (1 - this->getAnchorPoint().x), this->getPosition().y));
            }
            if (this->getPosition().y + boundBox.size.height * (1 - this->getAnchorPoint().y) < _panBoundsRect.size.height +
                _panBoundsRect.origin.y)
            {
                CCNode::setPosition(ccp(this->getPosition().x, _panBoundsRect.size.height + _panBoundsRect.origin.y -
                    boundBox.size.height * (1 - this->getAnchorPoint().y)));
            }
        }
    }
}

void Game::setScale(float scale){
    CCLayer::setScale( MIN(MAX(scale, _minScale), _maxScale));
}

void Game::recoverPositionAndScale(){
    if (!_panBoundsRect.equals(CCRectZero))
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        float rightEdgeDistance = this->rightEdgeDistance();
        float leftEdgeDistance = this->leftEdgeDistance();
        float topEdgeDistance = this->topEdgeDistance();
        float bottomEdgeDistance = this->bottomEdgeDistance();
        float scale = this->minPossibleScale();

        if (!rightEdgeDistance && !leftEdgeDistance && !topEdgeDistance && !bottomEdgeDistance)
        {
            return;
        }

        if (this->getScale() < scale)
        {
            _rubberEffectRecovering = true;
            CCPoint newPosition = CCPointZero;
            if (rightEdgeDistance && leftEdgeDistance && topEdgeDistance && bottomEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * (this->getAnchorPoint().x - 0.5f);
                float dy = scale * this->getContentSize().height * (this->getAnchorPoint().y - 0.5f);
                newPosition = ccp(winSize.width * 0.5f + dx, winSize.height * 0.5f + dy);
            }
            else if (rightEdgeDistance && leftEdgeDistance && topEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * (this->getAnchorPoint().x - 0.5f);
                float dy = scale * this->getContentSize().height * (1.0f - this->getAnchorPoint().y);
                newPosition = ccp(winSize.width * 0.5f + dx, winSize.height - dy);
            }
            else if (rightEdgeDistance && leftEdgeDistance && bottomEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * (this->getAnchorPoint().x - 0.5f);
                float dy = scale * this->getContentSize().height * this->getAnchorPoint().y;
                newPosition = ccp(winSize.width * 0.5f + dx, dy);
            }
            else if (rightEdgeDistance && topEdgeDistance && bottomEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * (1.0f - this->getAnchorPoint().x);
                float dy = scale * this->getContentSize().height * (this->getAnchorPoint().y - 0.5f);
                newPosition = ccp(winSize.width  - dx, winSize.height  * 0.5f + dy);
            }
            else if (leftEdgeDistance && topEdgeDistance && bottomEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * this->getAnchorPoint().x;
                float dy = scale * this->getContentSize().height * (this->getAnchorPoint().y - 0.5f);
                newPosition = ccp(dx, winSize.height * 0.5f + dy);
            }
            else if (leftEdgeDistance && topEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * this->getAnchorPoint().x;
                float dy = scale * this->getContentSize().height * (1.0f - this->getAnchorPoint().y);
                newPosition = ccp(dx, winSize.height - dy);
            }
            else if (leftEdgeDistance && bottomEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * this->getAnchorPoint().x;
                float dy = scale * this->getContentSize().height * this->getAnchorPoint().y;
                newPosition = ccp(dx, dy);
            }
            else if (rightEdgeDistance && topEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * (1.0f - this->getAnchorPoint().x);
                float dy = scale * this->getContentSize().height * (1.0f - this->getAnchorPoint().y);
                newPosition = ccp(winSize.width - dx, winSize.height - dy);
            }
            else if (rightEdgeDistance && bottomEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * (1.0f - this->getAnchorPoint().x);
                float dy = scale * this->getContentSize().height * this->getAnchorPoint().y;
                newPosition = ccp(winSize.width - dx, dy);
            }
            else if (topEdgeDistance || bottomEdgeDistance)
            {
                float dy = scale * this->getContentSize().height * (this->getAnchorPoint().y - 0.5f);
                newPosition = ccp(this->getPosition().x, winSize.height * 0.5f + dy);
            }
            else if (leftEdgeDistance || rightEdgeDistance)
            {
                float dx = scale * this->getContentSize().width * (this->getAnchorPoint().x - 0.5f);
                newPosition = ccp(winSize.width * 0.5f + dx, this->getPosition().y);
            }

            CCMoveTo *moveToPosition = CCMoveTo::create( _rubberEffectRecoveryTime,newPosition);
            CCScaleTo *scaleToPosition = CCScaleTo::create( _rubberEffectRecoveryTime,scale);
            CCFiniteTimeAction *sequence = CCSpawn::create(scaleToPosition, moveToPosition, CCCallFunc::create( this, callfunc_selector(Game::recoverEnded)), NULL);
            this->runAction(sequence);

        }
        else
        {
            _rubberEffectRecovering = false;
            CCMoveTo *moveToPosition = CCMoveTo::create(_rubberEffectRecoveryTime,ccp(this->getPosition().x + rightEdgeDistance - leftEdgeDistance,
                this->getPosition().y + topEdgeDistance - bottomEdgeDistance));
            CCFiniteTimeAction *sequence = CCSpawn::create(moveToPosition, CCCallFunc::create( this, callfunc_selector(Game::recoverEnded)), NULL);
            this->runAction(sequence);

        }
    }
}

void Game::recoverEnded(){
    _rubberEffectRecovering = false;
}

float Game::topEdgeDistance(){
    CCRect boundBox = this->boundingBox();
    return (int)(MAX(_panBoundsRect.size.height + _panBoundsRect.origin.y - this->getPosition().y -
        boundBox.size.height * (1 - this->getAnchorPoint().y), 0));
}

float Game::leftEdgeDistance(){
    CCRect boundBox = this->boundingBox();
    return (int)(MAX(this->getPosition().x - boundBox.size.width * this->getAnchorPoint().x - _panBoundsRect.origin.x, 0));
}

float Game::bottomEdgeDistance(){
    CCRect boundBox = this->boundingBox();
    return (int)(MAX(this->getPosition().y - boundBox.size.height * this->getAnchorPoint().y - _panBoundsRect.origin.y, 0));
}

float Game::rightEdgeDistance(){
    CCRect boundBox = this->boundingBox();
    return (int)(MAX(_panBoundsRect.size.width + _panBoundsRect.origin.x - this->getPosition().x -
        boundBox.size.width * (1 - this->getAnchorPoint().x), 0));
}

float Game::minPossibleScale(){
    if (!_panBoundsRect.equals(CCRectZero))
    {
        return MAX(_panBoundsRect.size.width / this->getContentSize().width,
            _panBoundsRect.size.height /this->getContentSize().height);
    }
    else
    {
        return _minScale;
    }
}

CCLayerPanZoomFrameEdge Game::frameEdgeWithPoint( CCPoint point){
    bool isLeft = point.x <= _panBoundsRect.origin.x + _leftFrameMargin;
    bool isRight = point.x >= _panBoundsRect.origin.x + _panBoundsRect.size.width - _rightFrameMargin;
    bool isBottom = point.y <= _panBoundsRect.origin.y + _bottomFrameMargin;
    bool isTop = point.y >= _panBoundsRect.origin.y + _panBoundsRect.size.height - _topFrameMargin;

    if (isLeft && isBottom)
    {
        return kCCLayerPanZoomFrameEdgeBottomLeft;
    }
    if (isLeft && isTop)
    {
        return kCCLayerPanZoomFrameEdgeTopLeft;
    }
    if (isRight && isBottom)
    {
        return kCCLayerPanZoomFrameEdgeBottomRight;
    }
    if (isRight && isTop)
    {
        return kCCLayerPanZoomFrameEdgeTopRight;
    }

    if (isLeft)
    {
        return kCCLayerPanZoomFrameEdgeLeft;
    }
    if (isTop)
    {
        return kCCLayerPanZoomFrameEdgeTop;
    }
    if (isRight)
    {
        return kCCLayerPanZoomFrameEdgeRight;
    }
    if (isBottom)
    {
        return kCCLayerPanZoomFrameEdgeBottom;
    }

    return kCCLayerPanZoomFrameEdgeNone;
}

float Game::horSpeedWithPosition(CCPoint pos){
    CCLayerPanZoomFrameEdge edge = this->frameEdgeWithPoint(pos);
    float speed = 0.0f;
    if (edge == kCCLayerPanZoomFrameEdgeLeft)
    {
        speed = _minSpeed + (_maxSpeed - _minSpeed) *
            (_panBoundsRect.origin.x + _leftFrameMargin - pos.x) / _leftFrameMargin;
    }
    if (edge == kCCLayerPanZoomFrameEdgeBottomLeft || edge == kCCLayerPanZoomFrameEdgeTopLeft)
    {
        speed = _minSpeed + (_maxSpeed - _minSpeed) *
            (_panBoundsRect.origin.x + _leftFrameMargin - pos.x) / (_leftFrameMargin * sqrt(2.0f));
    }
    if (edge == kCCLayerPanZoomFrameEdgeRight)
    {
        speed = - (_minSpeed + (_maxSpeed - _minSpeed) *
            (pos.x - _panBoundsRect.origin.x - _panBoundsRect.size.width +
            _rightFrameMargin) / _rightFrameMargin);
    }
    if (edge == kCCLayerPanZoomFrameEdgeBottomRight || edge == kCCLayerPanZoomFrameEdgeTopRight)
    {
        speed = - (_minSpeed + (_maxSpeed - _minSpeed) *
            (pos.x - _panBoundsRect.origin.x - _panBoundsRect.size.width +
            _rightFrameMargin) / (_rightFrameMargin * sqrt(2.0f)));
    }
    return speed;
}

float Game::vertSpeedWithPosition(CCPoint pos){
    CCLayerPanZoomFrameEdge edge = this->frameEdgeWithPoint(pos);
    float speed = 0.0f;
    if (edge == kCCLayerPanZoomFrameEdgeBottom)
    {
        speed = _minSpeed + (_maxSpeed - _minSpeed) *
            (_panBoundsRect.origin.y + _bottomFrameMargin - pos.y) / _bottomFrameMargin;
    }
    if (edge == kCCLayerPanZoomFrameEdgeBottomLeft || edge == kCCLayerPanZoomFrameEdgeBottomRight)
    {
        speed = _minSpeed + (_maxSpeed - _minSpeed) *
            (_panBoundsRect.origin.y + _bottomFrameMargin - pos.y) / (_bottomFrameMargin * sqrt(2.0f));
    }
    if (edge == kCCLayerPanZoomFrameEdgeTop)
    {
        speed = - (_minSpeed + (_maxSpeed - _minSpeed) *
            (pos.y - _panBoundsRect.origin.y - _panBoundsRect.size.height +
            _topFrameMargin) / _topFrameMargin);
    }
    if (edge == kCCLayerPanZoomFrameEdgeTopLeft || edge == kCCLayerPanZoomFrameEdgeTopRight)
    {
        speed = - (_minSpeed + (_maxSpeed - _minSpeed) *
            (pos.y - _panBoundsRect.origin.y - _panBoundsRect.size.height +
            _topFrameMargin) / (_topFrameMargin * sqrt(2.0f)));
    }
    return speed;
}
