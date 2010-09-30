//
//  GLES1RenderEngine.m
//  Electric3D
//
//  Created by Robert McDowell on 22/09/2010.
//  Copyright 2010 Electric TopHat Ltd. All rights reserved.
//

#import "GLES1RenderEngine.h"
#import "GLVertexTypes.h"

#import "GLScene.h"
#import "GLCamera.h"

#import "glu.h"

namespace GLRenderers 
{
#pragma mark ---------------------------------------------------------
#pragma mark Constructor / Destructor
#pragma mark ---------------------------------------------------------
	
	// --------------------------------------------------
	// Constructor
	// --------------------------------------------------
	GLES1RenderEngine::GLES1RenderEngine()
	: m_renderbuffer ( 0 )
	, m_framebuffer  ( 0 )
	, m_depthbuffer  ( 0 )
	, m_width		 ( 320 )
	, m_height		 ( 480 )
	, m_clearValue   ( GL_COLOR_BUFFER_BIT )
	{
	}
	
	// --------------------------------------------------
	// Destructor
	// --------------------------------------------------
	GLES1RenderEngine::~GLES1RenderEngine()
	{
	}
	
#pragma mark ---------------------------------------------------------
#pragma mark End Constructor / Destructor
#pragma mark ---------------------------------------------------------
	
#pragma mark ---------------------------------------------------------
#pragma mark Public Functions
#pragma mark ---------------------------------------------------------
	
	// ----------------------------------------------
	// Create the Render Buffer
	// ----------------------------------------------
	void GLES1RenderEngine::createRenderBuffer()
	{
		if ( m_renderbuffer == 0 )
		{
			glGenRenderbuffersOES(1, &m_renderbuffer);
			glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderbuffer);
		}
	}
	
	// ----------------------------------------------
	// Create the Frame Buffer
	// ----------------------------------------------
	void GLES1RenderEngine::createFrameBuffer()
	{
		if ( ( m_renderbuffer ) && ( m_framebuffer == 0 ) )
		{
			glGenFramebuffersOES(1, &m_framebuffer);
			glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_framebuffer);
			glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, m_renderbuffer);
		}
		
		glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &m_width);
		glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &m_height);
	}
	
	// ----------------------------------------------
	// Create the Depth Buffer
	// ----------------------------------------------
	void GLES1RenderEngine::createDepthBuffer()
	{
		if ( ( m_renderbuffer ) && ( m_framebuffer ) && ( m_depthbuffer == 0 ) )
		{
			glGenRenderbuffersOES(1, &m_depthbuffer);
			glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_depthbuffer);
			glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, m_width, m_height);
			glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, m_depthbuffer);
			
			glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderbuffer);
			
			m_clearValue |= GL_DEPTH_BUFFER_BIT;
		}
	}
	
	// ----------------------------------------------
	// Destroy the Render Buffer
	// ----------------------------------------------
	void GLES1RenderEngine::destroyRenderBuffer()
	{
		if( m_renderbuffer ) 
		{
			glDeleteRenderbuffersOES(1, &m_renderbuffer);
			m_renderbuffer = 0;
		}
	}
	
	// ----------------------------------------------
	// Destroy the Frame Buffer
	// ----------------------------------------------
	void GLES1RenderEngine::destroyFrameBuffer()
	{
		if( m_framebuffer )
		{
			glDeleteFramebuffersOES(1, &m_framebuffer);
			m_framebuffer = 0;
		}
	}
	
	// ----------------------------------------------
	// Destroy the Depth Buffer
	// ----------------------------------------------
	void GLES1RenderEngine::destroyDepthBuffer()
	{
		if( m_depthbuffer ) 
		{
			glDeleteRenderbuffersOES(1, &m_depthbuffer);
			m_depthbuffer = 0;
		}
	}
	
	// --------------------------------------------------
	// rebind the buffers to the context
	// --------------------------------------------------
	void GLES1RenderEngine::rebindBuffers()
	{
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderbuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_framebuffer);
	}
	
	// --------------------------------------------------
	// Initialize
	// --------------------------------------------------
	void GLES1RenderEngine::initialize()
	{	
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		
		glViewport(0, 0, m_width, m_height);
		
		m_perspective.setAspect( (float)m_width / (float)m_height );
		
		if ( m_depthbuffer )
		{
			glEnable(GL_DEPTH_TEST);
		}
		else 
		{
			glDisable(GL_DEPTH_TEST);
		}
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		
		GLfloat lightAmbient[]		= { 0.6f, 0.6f, 0.6f, 1.0f };
		GLfloat lightDiffuse[]		= { 0.6f, 0.6f, 0.6f, 1.0f };
		GLfloat lightSpecular[]		= { 0.6f, 0.6f, 0.6f, 1.0f };
		
		glLightfv( GL_LIGHT0, GL_AMBIENT,  lightAmbient );
		glLightfv( GL_LIGHT0, GL_DIFFUSE,  lightDiffuse );
		glLightfv( GL_LIGHT0, GL_SPECULAR, lightSpecular );
		
		//GLfloat lightmodelAmbient[]	= { 0.2f, 0.2f, 0.2f, 1.0f };
		//GLfloat lightmodelDiffuse[]	= { 0.2f, 0.2f, 0.2f, 1.0f };
		//glLightModelfv( GL_AMBIENT, lightmodelAmbient );
		//glLightModelfv( GL_DIFFUSE, lightmodelDiffuse );
	
		GLfloat matAmbient[]		= { 0.6f, 0.6f, 0.6f, 1.0f };
		GLfloat matDiffuse[]		= { 0.6f, 0.6f, 0.6f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
		
		glShadeModel(GL_SMOOTH);
		
		m_Renderer.initialize();
	}
	
	// --------------------------------------------------
	// Teardown
	// --------------------------------------------------
	void GLES1RenderEngine::teardown()
	{
		m_Renderer.teardown();
	}
	
	// --------------------------------------------------
	// set the Clear GLColor
	// --------------------------------------------------
	void GLES1RenderEngine::setClearColor( float _red, float _green, float _blue )
	{
		glClearColor(_red, _green, _blue, 1.0f);
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GLES1RenderEngine::update( float _timeStep )
	{
	}
	
	// --------------------------------------------------
	// Render the Scene
	// --------------------------------------------------
	void GLES1RenderEngine::render()
	{
		//glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_framebuffer);
		
		updateCameraPersepctive();
		
		glClear(m_clearValue);
		
		glMatrixMode(GL_MODELVIEW);	
		
		setupCamera();
		
		m_Renderer.render();
		
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderbuffer);
	}
	
	// --------------------------------------------------
	// On Rotate
	// --------------------------------------------------
	void GLES1RenderEngine::onRotate( eDeviceOrientation _newOrientation )
	{
	}
	
	// --------------------------------------------------
	// contains the scene
	// --------------------------------------------------
	BOOL GLES1RenderEngine::contains( GLObjects::GLScene * _scene )
	{
		return m_Renderer.contains( _scene );
	}
	
	// --------------------------------------------------
	// add the Scene to the render
	// --------------------------------------------------
	void GLES1RenderEngine::add( GLObjects::GLScene * _scene )
	{
		m_Renderer.add( _scene );
	}
	
	// --------------------------------------------------
	// remove the Scene from the render
	// --------------------------------------------------
	void GLES1RenderEngine::remove( GLObjects::GLScene * _scene )
	{
		m_Renderer.remove( _scene );
	}
	
#pragma mark ---------------------------------------------------------
#pragma mark End Public Functions
#pragma mark ---------------------------------------------------------
	
	
#pragma mark ---------------------------------------------------------
#pragma mark Private Functions
#pragma mark ---------------------------------------------------------
	
	// --------------------------------------------------
	// Update the camera Perspective
	// --------------------------------------------------
	void GLES1RenderEngine::updateCameraPersepctive()
	{
		// --------------------------------------
		// Update the camera perspective
		// --------------------------------------
		if ( m_perspective.isDirty() )
		{
			CGMaths::CGMatrix4x4 perspective;
			m_perspective.resetFlags();
			if ( m_perspective.convertToMatrix( perspective ) )
			{
				glMatrixMode(GL_PROJECTION);
				glLoadMatrixf( perspective.m );
			}
		}
		// --------------------------------------
	}
	
	// --------------------------------------------------
	// Setup the camera
	// --------------------------------------------------
	void GLES1RenderEngine::setupCamera()
	{
		// --------------------------------------
		// Correct the camera and split to 
		// be rotation and translation
		// --------------------------------------
		const CGMaths::CGMatrix4x4 & matrix = m_camera.transform();
		
		CGMaths::CGMatrix4x4 rotation		= CGMaths::CGMatrix4x4Identity;

		// copy the right axis
		rotation.m[0]  = matrix.m[0];
		rotation.m[4]  = matrix.m[4];
		rotation.m[8]  = matrix.m[8];
		
		// copy the up axis
		rotation.m[1]  = matrix.m[1];
		rotation.m[5]  = matrix.m[5];
		rotation.m[9]  = matrix.m[9];
		
		// copy and flip the at
		rotation.m[2]  = -matrix.m[2];
		rotation.m[6]  = -matrix.m[6];
		rotation.m[10] = -matrix.m[10];
		// --------------------------------------
		
		// --------------------------------------
		// Update the gl camera 
		// --------------------------------------		
		glLoadMatrixf( rotation.m );
		glTranslatef( -matrix.m[12], -matrix.m[13], -matrix.m[14] );
		// --------------------------------------
	}
	
#pragma mark ---------------------------------------------------------
#pragma mark End Private Functions
#pragma mark ---------------------------------------------------------
	
};