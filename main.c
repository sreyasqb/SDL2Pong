#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
static const int width=1200,height=900;






int main(int argc,char **argv)
{
    
    
    //SDL SYNTAX
    SDL_Init((SDL_INIT_VIDEO));
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *window = SDL_CreateWindow("Virtual Keyboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer=SDL_CreateRenderer(window, -1,0);
    SDL_Event event;
    
    
    int movement[]={0,0,0,0};
    //DEFINING P1
    SDL_Rect p1;
    p1.x=10;
    p1.y=450;
    p1.h=100;
    p1.w=15;
    //DEFINING P2
    SDL_Rect p2;
    p2.x=1180;
    p2.y=450;
    p2.h=100;
    p2.w=15;
    //DEFINING BALL
    SDL_Rect ball;
    ball.x=595;
    ball.y=300;
    ball.h=10;
    ball.w=10;
    //PLAYER AND BALL VELOCITIES
    int bvx=-1,bvy=-1;
    int hit=0;
    int p1v=1;
    int p2v=1;
    //SCORE VARIABLES
    int p1score[3]={1,1,1},p2score[3]={1,1,1},p1Counter=2,p2Counter=0;
    
    int run=1;
    
    int point=0,start=0;
    
    while (run)
    {
       
        
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    run=0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            movement[2]=1;
                            break;
                        case SDLK_DOWN:
                            movement[3]=1;
                            break;
                        case SDLK_w:
                            movement[0]=1;
                            break;
                        case SDLK_s:
                            movement[1]=1;
                            break;
                        case SDLK_t:
                            start=1;
                            break;
                        
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            movement[2]=0;
                            break;
                        case SDLK_DOWN:
                            movement[3]=0;
                            break;
                        case SDLK_w:
                            movement[0]=0;
                            break;
                        case SDLK_s:
                            movement[1]=0;
                            break;
                        case SDLK_t:
                            start=0;
                            break;
                        
                    }
                    break;
            }
            
        }
        
        //PLAYER CONTROL STATEMENTS
        
        if (movement[0] && p1.y>100 && !point)
            p1.y-=p1v;
        if (movement[1] &&p1.y<800 && !point)
            p1.y+=p1v;
        if (movement[2] && p2.y>100 && !point)
            p2.y-=p2v;
        if (movement[3] &&p2.y<800 && !point)
            p2.y+=p2v;
        
        //BALL CONTROL STATEMENTS
        if (!hit)
        {
            ball.x+=bvx;
            ball.y-=bvy;
        }
        
        //BALL COLLISION PHYSICS WITH PLAYER
        if ((p1.x+p1.w)>ball.x && ball.y>p1.y && ball.y<p1.y+p1.h)
        {
            hit=1;
            bvx=-bvx;

        }
        if (ball.x+ball.w>p2.x && ball.y>p2.y && ball.y<p2.y+p2.h)
        {
            hit=1;
            bvx=-bvx;
            
        }
        //BALL COLLISION PHYSICS WITH TOP AND BOTTOM BARS
        if (ball.y<100)
        {
            bvy=-bvy;
        }
        else if (ball.y+ball.h>900)
        {
            bvy=-bvy;
        }
        
        
        //BALL MOVEMENT
        if (hit && !point)
        {
            
            ball.x+=bvx;
            
            ball.y+=bvy;
        }
        
        //CHECKING WIN CONDITION
        if (ball.x<10 /*&& p1Counter>0*/ && !point)
        {
            p1score[p1Counter]=0;
            p1Counter--;
            point=1;
        }
        if (ball.x>1190 /*&& p2Counter<3*/ && !point)
        {
            p2score[p2Counter]=0;
            p2Counter++;
            point=1;
            
        }
        // IF POINT IS SCORED THEN RESETING THE FRAME
        if (start)
        {
            point=0;
            ball.x=595;
            ball.y=300;
            p1.x=10;
            p1.y=450;
            p2.x=1180;
            p2.y=450;
            hit=0;
            
        }
       
        
        
        
        
        
        
        //background overlay
        //background color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        
        
        
        
        //background rectangle
        SDL_Rect bgRect;
        bgRect.x=0;
        bgRect.y=0;
        bgRect.h=100;
        bgRect.w=1200;
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
        SDL_RenderDrawRect(renderer, &bgRect);
        SDL_RenderFillRect(renderer, &bgRect);
        
        //SCORE RECTANGLES
        //PLAYER 1 SCORE 1
        SDL_Rect score1Rect1;
        score1Rect1.x=60;
        score1Rect1.y=20;
        score1Rect1.h=60;
        score1Rect1.w=60;
        if (p1score[0])
        {
            SDL_SetRenderDrawColor(renderer, 156, 34, 93, 255);
        
            SDL_RenderDrawRect(renderer, &score1Rect1);
            SDL_RenderFillRect(renderer, &score1Rect1);
        }
        //PLAYER 1 SCORE 2
        
        SDL_Rect score1Rect2;
        score1Rect2.x=60+120;
        score1Rect2.y=20;
        score1Rect2.h=60;
        score1Rect2.w=60;
        if (p1score[1])
        {
            SDL_SetRenderDrawColor(renderer, 156, 34, 93, 255);
            SDL_RenderDrawRect(renderer, &score1Rect2);
            SDL_RenderFillRect(renderer, &score1Rect2);
        }
        //PLAYER 1 SCORE 3
        SDL_Rect score1Rect3;
        score1Rect3.x=60+240;
        score1Rect3.y=20;
        score1Rect3.h=60;
        score1Rect3.w=60;
        if (p1score[2])
        {
            SDL_SetRenderDrawColor(renderer, 156, 34, 93, 255);
            SDL_RenderDrawRect(renderer, &score1Rect3);
            SDL_RenderFillRect(renderer, &score1Rect3);
        }
        
        
        //PLAYER 2 SCORE 1
        SDL_Rect score2Rect1;
        score2Rect1.x=840;
        score2Rect1.y=20;
        score2Rect1.h=60;
        score2Rect1.w=60;
        if (p2score[0])
        {
            SDL_SetRenderDrawColor(renderer, 156, 34, 93, 255);
            SDL_RenderDrawRect(renderer, &score2Rect1);
            SDL_RenderFillRect(renderer, &score2Rect1);
        }
        //PLAYER 2 SCORE 2
        
        SDL_Rect score2Rect2;
        score2Rect2.x=840+120+120;
        score2Rect2.y=20;
        score2Rect2.h=60;
        score2Rect2.w=60;
        if (p2score[2])
        {
            SDL_SetRenderDrawColor(renderer, 156, 34, 93, 255);
            SDL_RenderDrawRect(renderer, &score2Rect2);
            SDL_RenderFillRect(renderer, &score2Rect2);
        }
        
        //PLAYER 2 SCORE 3
        SDL_Rect score2Rect3;
        score2Rect3.x=840+120;
        score2Rect3.y=20;
        score2Rect3.h=60;
        score2Rect3.w=60;
        if (p2score[1])
        {
            SDL_SetRenderDrawColor(renderer, 156, 34, 93, 255);
            SDL_RenderDrawRect(renderer, &score2Rect3);
            SDL_RenderFillRect(renderer, &score2Rect3);
        }
        
        
        
        //center rectangle
        SDL_Rect cRect;
        cRect.x=595;
        cRect.y=100;
        cRect.h=800;
        cRect.w=10;
        SDL_SetRenderDrawColor(renderer, 154, 157, 236, 255);
        SDL_RenderDrawRect(renderer, &cRect);
        SDL_RenderFillRect(renderer, &cRect);
        
        
        
        //rectangle 1
        SDL_SetRenderDrawColor(renderer, 0, 65, 89, 255);
        SDL_RenderDrawRect(renderer, &p1);
        SDL_RenderFillRect(renderer, &p1);
        //rectangle 2
        SDL_SetRenderDrawColor(renderer, 0, 197, 144, 255);
        SDL_RenderDrawRect(renderer, &p2);
        SDL_RenderFillRect(renderer, &p2);
        //
        SDL_SetRenderDrawColor(renderer, 237, 41, 57, 255);
        SDL_RenderDrawRect(renderer, &ball);
        SDL_RenderFillRect(renderer, &ball);
        
        
        
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
