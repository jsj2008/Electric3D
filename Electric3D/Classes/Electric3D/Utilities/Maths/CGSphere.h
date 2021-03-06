/*
 *  CGSphere.h
 *  Electric3D
 *
 *  Created by Robert McDowell on 30/09/2010.
 *  Copyright 2010 Electric TopHat Ltd. All rights reserved.
 *
 */

#if !defined(_CGSphere_h__)
#define __CGSphere_h__

#import "CGMathsConstants.h"
#import "CGMathsTypes.h"

namespace CGMaths 
{
#pragma mark ---------------------------------------------------------
#pragma mark CGSphere consts 
#pragma mark ---------------------------------------------------------
	
	const CGSphere CGSphereZero = {  0.0f,  0.0f,  0.0f, 0.0f };
	const CGSphere CGSphereUnit = {  0.0f,  0.0f,  0.0f, 1.0f };
	
#pragma mark ---------------------------------------------------------
#pragma mark End CGSphere consts 
#pragma mark ---------------------------------------------------------

#pragma mark ---------------------------------------------------------
#pragma mark CGSphere Functions
#pragma mark ---------------------------------------------------------

	// ---------------------------------------------------
	// Does the line intersect with the CGSphere
	// ---------------------------------------------------
	inline BOOL CGSphereIntersects( const CGSphere & _sphere, const CGVector3D & _start, const CGVector3D & _end )
	{
		CGVector3D point = CGVector3DMakeClosestPoint( _sphere.center, _start, _end );	
		CGVector3D lineC = CGVector3DMakeSub( _sphere.center, point );
		float lenc = CGVector3DLengthSquared( lineC );
		return ( lenc <= ( _sphere.radius * _sphere.radius ) );
	}
	
#pragma mark ---------------------------------------------------------
#pragma mark End CGSphere Functions
#pragma mark ---------------------------------------------------------
	
#pragma mark ---------------------------------------------------------
#pragma mark CGSphere Make Functions
#pragma mark ---------------------------------------------------------
	
	// ---------------------------------------------------
	// Make a CGSphere
	// ---------------------------------------------------
	inline CGSphere CGSphereMake( float _x, float _y, float _z,float _r )
	{
		CGSphere sphere; 
		sphere.center.x = _x;
		sphere.center.x = _y;
		sphere.center.x = _z;
		sphere.radius   = _r;
		return sphere;
	}
	
	// ---------------------------------------------------
	// Make a CGSphere
	// ---------------------------------------------------
	inline CGSphere CGSphereMake( const CGAABB & _aabb )
	{
		CGVector3D line = CGVector3DMakeSub( _aabb.max, _aabb.min );
		
		CGSphere sphere; 
		sphere.center = CGAABBGetCenter(_aabb);
		sphere.radius = CGVector3DLength( line ) * 0.5f;
		return sphere;
	}
	
#pragma mark ---------------------------------------------------------
#pragma mark End CGSphere Make Functions
#pragma mark ---------------------------------------------------------
	
};

#endif