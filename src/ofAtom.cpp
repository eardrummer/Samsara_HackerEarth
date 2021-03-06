/*
*  This is part of the Samsara Project, by Manaswi, Siddharth and Kushagra 
*  No part of this code may be used(directly or modified) without contacting the authors
*
*  This is an experimental physics based virtual sound system project and we hope to develop it further and release it in the future
*  11 July 2018
*
*    Contact : manaswimishra17@gmail.com
*/

#include "ofAtom.h"


//-----------------------------------------------------------------------------
ofAtom::ofAtom(int type, int id, int posX , int posY, int radius){
    
    m_type = type;  // See ofAtom.h for type
    m_id = id;
    m_posX = posX;
    m_posY = posY;
    m_radius = radius;
    
    if(type != 3){
        m_velocityX = ofRandom(-10, 10);
        m_velocityY = ofRandom(-10, 10);
        
        if(m_velocityX == 0)
            m_velocityX = 1;
        if(m_velocityY == 0)
            m_velocityY = 1;
    }
    
    if(type == 3){
        m_velocityX = 0;
        m_velocityY = 0;
    }
    // Give different Mass to each type of atom
    m_mass = 5;
    
}


//-------------------------------------------------------------------------------
void ofAtom::update(){
    
    //updating the virtual atoms
    if(m_type == 3){
        m_velocityX = 0;
        m_velocityY = 0;
    }
    else {
        
        m_posX = m_posX + (m_velocityX);
        m_posY = m_posY + (m_velocityY);
        
        if (m_posX < m_radius || m_posX > ofGetWidth() - m_radius) {
            m_velocityX = -1 * m_velocityX;
            
        }
        
        if (m_posY < m_radius || m_posY > ofGetHeight() - m_radius) {
            m_velocityY = -1 * m_velocityY;
        }
        
        if (m_posX < m_radius)
            m_posX = m_radius;
        if (m_posY < m_radius)
            m_posY = m_radius;
        if (m_posX > ofGetWidth() - m_radius)
            m_posX = ofGetWidth() - m_radius;
        if (m_posY > ofGetHeight() - m_radius)
            m_posY = ofGetHeight() - m_radius;
    }
}

//--------------------------------------------------------------------------------
void ofAtom::draw(){
    
    ofFill();
    
    if(m_type == 0)
        ofSetColor(225,255,255); // Any Change to the color of Creator should also be reflected in ofApp::Granulate()
    else if(m_type == 1)
        ofSetColor(60,250,115);
    else if(m_type == 2)
        ofSetColor(255,60,0);
    else if(m_type == 3 && m_id == 0){
	ofSetColor(255,255,255);
	ofNoFill();
	ofSetLineWidth(50);
	}
	//ofSetColor(cyanPrint);
    else if(m_type == 3 && m_id == 1){
	 ofSetColor(60,250,115);
	ofSetLineWidth(50);
	ofNoFill();
	}
	//ofSetColor(yellowPrint);
    else if(m_type == 3 && m_id == 2){
	//ofSetColor(magentaPrint);
	 ofSetColor(255,60,0);
	ofSetLineWidth(50);
	ofNoFill();
	}
    else if(m_type == 4)
	ofSetColor(112,112,112);
	//Insert Color for Frozen Creator
    else if(m_type == 5)
	 ofSetColor(30,125,55);
	//Insert Color for Frozen Preserver
    else if(m_type == 6)
	 ofSetColor(112,30,0);
	//Insert Color for Frozen Invisible Creator
    else if(m_type == 7 && m_id == 0){
	ofSetColor(112,112,112);
	ofSetLineWidth(20);
	ofNoFill();
	}
        //Insert Color for Frozen Invisible Preserver
    else if(m_type == 7 && m_id == 1){
        ofSetColor(30,125,55);
	ofNoFill();
	ofSetLineWidth(20);
	}
        //Insert Color for Frozen Invisible Destroyer
    else if(m_type == 7 && m_id == 2){
        ofSetColor(112,30,0);
	ofNoFill();
	ofSetLineWidth(20);
	}

    ofDrawCircle(m_posX, m_posY, m_radius);
    
}

//--------------------------------------------------------------------------------
int ofAtom::collide(ofAtom* nearAtom){
    
    
    if(ofDist(nearAtom->m_posX, nearAtom->m_posY, m_posX, m_posY) < nearAtom->m_radius + m_radius) {
        
        if(nearAtom->m_type != 3){
            
            float newVelX1 = (m_velocityX * (m_mass - nearAtom->m_mass) + (2 * nearAtom->m_mass * nearAtom->m_velocityX)) / float(m_mass + nearAtom->m_mass);
            float newVelY1 = (m_velocityY * (m_mass - nearAtom->m_mass) + (2 * nearAtom->m_mass * nearAtom->m_velocityY)) / float(m_mass + nearAtom->m_mass);
            float newVelX2 = (nearAtom->m_velocityX * (nearAtom->m_mass - m_mass) + (2 * m_mass * m_velocityX)) / float(m_mass + nearAtom->m_mass);
            float newVelY2 = (nearAtom->m_velocityY * (nearAtom->m_mass - m_mass) + (2 * m_mass * m_velocityY)) / float(m_mass + nearAtom->m_mass);
            
            
            m_velocityX = newVelX1;
            m_velocityY = newVelY1;
            
            nearAtom->m_velocityX = newVelX2;
            nearAtom->m_velocityY = newVelY2;
            
            nearAtom->update();
            update();
            
        }
        else {
            
            m_velocityX *= -1;
            m_velocityY *= -1;
            
            update();
            
        }
        // cout<<"VELOCITY"<<" "<<m_velocityX<<" "<<m_velocityY<<endl;
        
        
        // To check if one atom is overlapping another atom
        while(ofDist(nearAtom->m_posX, nearAtom->m_posY, m_posX, m_posY) < nearAtom->m_radius + m_radius){
            
            m_posX += ofSign(m_velocityX);
            m_posY += ofSign(m_velocityY);
            
        }
        
        
        
        
        //MESSAGE AND RETURN TO INDICATE TYPE OF COLLISION:
        if (m_type == 0 && nearAtom->m_type == 1) {
            //    	    cout<<" EFFECTS Collision:"<<m_type<<" "<<m_posX<<","<<m_posY<<" "<<nearAtom->m_type<<" "<<nearAtom->m_posX<<","<<nearAtom->m_posY<<endl;
            return 1;
        }
        else if (m_type == 0 && nearAtom->m_type == 2) {
            //    	    cout<<" DESTROY Collision:"<<m_type<<" "<<m_posX<<","<<m_posY<<" "<<nearAtom->m_type<<" "<<nearAtom->m_posX<<","<<nearAtom->m_posY<<endl;
            return 2;
        }
        else if (m_type == 0 && nearAtom->m_type == 3){
            return 3;
        }
        
        return 1; // For all other types of collisions.
        
    }
    
    
    return 0;   //No Collision occured
}

//-----------------------------------------------------------------------------------------
void ofAtom::assignVelocity(int velocityX, int velocityY){
    
    
    m_velocityX = velocityX;
    m_velocityY = velocityY;
    
    if(velocityX > 7)
        m_velocityX = 7;
    else if(velocityX < -7)
        m_velocityX = -7;
    
    if(velocityY > 7)
        m_velocityY = 7;
    else if(velocityY < -7)
        m_velocityY = -7;
    
    
    // Giving a slight velocity to all Atoms (except the virtual atoms, m_type = 3)
    if(velocityX == 0 && m_type < 3)
        m_velocityX = 1;
    
    if(velocityY == 0 && m_type < 3)
        m_velocityY = 1;
    
    
}


//---------------------------------------------------------------------------------------

void ofAtom::assign(int type, int id, int posX, int posY, int velocityX, int velocityY, int radius){
    
    m_type = type;
    m_id = id;
    m_posX = posX;
    m_posY = posY;
    m_velocityX = velocityX;
    m_velocityY = velocityY;
    m_radius = radius;
    
}

//---------------------------------------------------------------------------------------

void ofAtom::assign(int type, int id, int posX, int posY, int radius){

    m_type = type;
    m_id = id;
    m_posX = posX;
    m_posY = posY;
    m_radius = radius;

        m_velocityX = ofRandom(-10, 10);
        m_velocityY = ofRandom(-10, 10);

        if(m_velocityX == 0)
            m_velocityX = 1;
        if(m_velocityY == 0)
            m_velocityY = 1;

}


//----------------------------------------------------------------------------------------
float ofAtom::atomFxDist(ofAtom* PAtom){
    
    float Distance;
    Distance = ofDist(PAtom->m_posX, PAtom->m_posY, m_posX, m_posY);
    
    return Distance;
}


//----------------------------------------------------------------------------------------------
//void ofAtom::~ofAtom(){


//	TODO:delete this 


//}




