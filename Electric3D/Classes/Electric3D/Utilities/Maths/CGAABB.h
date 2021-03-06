/*
 *  CGAABB.h
 *  Electric3D
 *
 *  Created by Robert McDowell on 24/09/2010.
 *  Copyright 2010 Electric TopHat Ltd. All rights reserved.
 *
 */

#if !defined(__CGAABB_h__)
#define __CGAABB_h__

#import "CGMathsConstants.h"
#import "CGMathsTypes.h"

namespace CGMaths 
{

#pragma mark ---------------------------------------------------------
#pragma mark CGAABB consts 
#pragma mark ---------------------------------------------------------
	
	const CGAABB CGAABBZero		= {  0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f };
	const CGAABB CGAABBUnit		= { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	const CGAABB CGAABBInvalid	= { MAXFLOAT, MAXFLOAT, MAXFLOAT, -MAXFLOAT, -MAXFLOAT, -MAXFLOAT };
	
#pragma mark ---------------------------------------------------------
#pragma mark End CGAABB consts 
#pragma mark ---------------------------------------------------------

#pragma mark ---------------------------------------------------------
#pragma mark CGAABB Functions
#pragma mark ---------------------------------------------------------
	
	// ---------------------------------------------------
	// Add a point to an existing AABB
	// ---------------------------------------------------
	inline void CGAABBAddPoint( CGAABB & _aabb, float _x, float _y, float _z )
	{
		_aabb.min.x = ( _aabb.min.x > _x ) ? _x : _aabb.min.x;
		_aabb.min.y = ( _aabb.min.y > _y ) ? _y : _aabb.min.y;
		_aabb.min.z = ( _aabb.min.z > _z ) ? _z : _aabb.min.z;
		
		_aabb.max.x = ( _aabb.max.x < _x ) ? _x : _aabb.max.x;
		_aabb.max.y = ( _aabb.max.y < _y ) ? _y : _aabb.max.y;
		_aabb.max.z = ( _aabb.max.z < _z ) ? _z : _aabb.max.z;
	}
	
	// ---------------------------------------------------
	// Add a point to an existing AABB
	// ---------------------------------------------------
	inline void CGAABBAddPoint( CGAABB & _aabb, const CGVector3D & _point )
	{
		CGAABBAddPoint( _aabb, _point.x, _point.y, _point.z );
	}
	
	// ---------------------------------------------------
	// Merge an AABB with another AABB
	// ---------------------------------------------------
	inline void CGAABBMerge( CGAABB & _aabbA, const CGAABB & _aabbB )
	{
		_aabbA.min.x = ( _aabbA.min.x > _aabbB.min.x ) ? _aabbB.min.x : _aabbA.min.x;
		_aabbA.min.y = ( _aabbA.min.y > _aabbB.min.y ) ? _aabbB.min.y : _aabbA.min.y;
		_aabbA.min.z = ( _aabbA.min.z > _aabbB.min.z ) ? _aabbB.min.z : _aabbA.min.z;
		_aabbA.max.x = ( _aabbA.max.x < _aabbB.max.x ) ? _aabbB.max.x : _aabbA.max.x;
		_aabbA.max.y = ( _aabbA.max.y < _aabbB.max.y ) ? _aabbB.max.y : _aabbA.max.y;
		_aabbA.max.z = ( _aabbA.max.z < _aabbB.max.z ) ? _aabbB.max.z : _aabbA.max.z;
	}
	
	// ---------------------------------------------------
	// Get the center of the AABB
	// ---------------------------------------------------
	inline CGVector3D CGAABBGetCenter( const CGAABB & _aabb )
	{
		return CGVector3DMake( _aabb.min.x + ( (_aabb.max.x - _aabb.min.x) * 0.5f ),
							   _aabb.min.y + ( (_aabb.max.y - _aabb.min.y) * 0.5f ),
							   _aabb.min.z + ( (_aabb.max.z - _aabb.min.z) * 0.5f ) );
	}
	
	// ---------------------------------------------------
	// Get the volume of the AABB
	// ---------------------------------------------------
	inline CGVector3D CGAABBGetVolume( const CGAABB & _aabb )
	{
		return CGVector3DMake( (_aabb.max.x - _aabb.min.x),
							   (_aabb.max.y - _aabb.min.y),
							   (_aabb.max.z - _aabb.min.z) );
	}
	
	// ---------------------------------------------------
	// Is point inside the AABB
	// ---------------------------------------------------
	inline BOOL CGAABBContains( const CGAABB & _aabb, const CGVector3D & _point )
	{
		return ( ( _point.x > _aabb.min.x && _point.x < _aabb.max.x ) &&
				 ( _point.y > _aabb.min.y && _point.y < _aabb.max.y ) &&
				 ( _point.z > _aabb.min.z && _point.z < _aabb.max.z ) );
	}
	
	// ---------------------------------------------------
	// Is point inside the AABB
	// ---------------------------------------------------
	inline BOOL CGAABBContains( const CGAABB & _aabbA, const CGAABB & _aabbB )
	{
		return CGAABBContains( _aabbA, _aabbB.min ) && 
		       CGAABBContains( _aabbA, _aabbB.max );
	}
	
	// ---------------------------------------------------
	// Is point inside or on the AABB
	// ---------------------------------------------------
	inline BOOL CGAABBContainsOrTouches( const CGAABB & _aabb, const CGVector3D & _point )
	{
		return ( ( _point.x >= _aabb.min.x && _point.x <= _aabb.max.x ) &&
				 ( _point.y >= _aabb.min.y && _point.y <= _aabb.max.y ) &&
				 ( _point.z >= _aabb.min.z && _point.z <= _aabb.max.z ) );
	}
	
	// ---------------------------------------------------
	// Does an AABB Intersect with the other AABB
	// ---------------------------------------------------
	inline BOOL CGAABBIntersects( const CGAABB & _aabbA, const CGAABB & _aabbB )
	{
		return CGAABBContainsOrTouches( _aabbA, _aabbB.min ) && 
		       CGAABBContainsOrTouches( _aabbA, _aabbB.max );
	}
	
	// ---------------------------------------------------
	// Does the line intersect with the AABB
	// ---------------------------------------------------
	inline BOOL CGAABBIntersects( const CGAABB & _aabb, const CGVector3D & _start, const CGVector3D & _end )
	{
		CGVector3D c	= CGAABBGetCenter( _aabb );
		CGVector3D e	= CGVector3DMakeSub( _aabb.max, c );
		CGVector3D mp	= CGVector3DMakeScale( CGVector3DMakeAdd( _start, _end ), 0.5f );
		CGVector3D d	= CGVector3DMakeSub( _start, mp );
		CGVector3D m	= CGVector3DMakeSub( mp, c );
		
		float adx = fabs(d.x);
		if ( fabs(m.x) > e.x + adx ) return FALSE;
		float ady = fabs(d.y);
		if ( fabs(m.y) > e.y + ady ) return FALSE;
		float adz = fabs(d.z);
		if ( fabs(m.z) > e.z + adz ) return FALSE;
		
		adx += EPSILON; ady += EPSILON; adz += EPSILON;
		
		if (fabs(m.y * d.z - m.z * d.y) > e.y * adz + e.z * ady ) return FALSE;
		if (fabs(m.z * d.x - m.x * d.z) > e.x * adz + e.z * adx ) return FALSE;
		if (fabs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx ) return FALSE;
		
		return TRUE;
	}
	
	inline BOOL CGAABBIntersects( const CGAABB & _aabb, const CGVector3D & _start, const CGVector3D & _end, CGVector3D & _contact )
	{
		float tmin = 0.0f;
		float tmax = MAXFLOAT;
		CGVector3D r	= CGVector3DMakeSub( _start, _end );
		int i;
		for ( i=0; i<3; i++) 
		{
			if ( fabs(r.v[i]) < EPSILON )
			{
				// ray parallel to slab, no contact if the
				// start is not in the AABB
				if ( ( _start.v[i] < _aabb.min.v[i] ) ||
					 ( _start.v[i] > _aabb.max.v[i] ) )
				{
					return FALSE;
				}
			}
			else 
			{
				// compute the t value of the ray 
				// with the near and far plane
				float ood = 1.0f / r.v[i];
				float t1  = (_aabb.min.v[i] - _start.v[i]) * ood;
				float t2  = (_aabb.max.v[i] - _start.v[i]) * ood;
				
				// make t1 be the intersection with the near plane, 
				// t2 with the far plane
				if ( t1 > t2 )
				{
					float t = t2;
					t2 = t1;
					t1 = t;
				}
				
				// compute the intersection of slap
				tmin = MAX( tmin, t1 );
				tmax = MIN( tmax, t2 );
				
				// exit with no collision as soon as 
				// there is no intersection
				if ( tmin > tmax ) return FALSE;
			}
		}
		
		_contact = CGVector3DMakeAdd( _start, r, tmin );
		return TRUE;
	}
	
#pragma mark ---------------------------------------------------------
#pragma mark End CGAABB Functions
#pragma mark ---------------------------------------------------------
	
#pragma mark ---------------------------------------------------------
#pragma mark CGAABB Make Functions
#pragma mark ---------------------------------------------------------
	
	// ---------------------------------------------------
	// Make a CGAABB
	// ---------------------------------------------------
	inline CGAABB CGAABBMake( float _xA, float _yA, float _zA,float _xB, float _yB, float _zB )
	{
		CGAABB aabb; 
		if ( _xA < _xB )
		{
			aabb.min.x = _xA;
			aabb.max.x = _xB;
		}
		else 
		{
			aabb.min.x = _xB;
			aabb.max.x = _xA;
		}
		if ( _yA < _yB )
		{
			aabb.min.y = _yA;
			aabb.max.y = _yB;
		}
		else 
		{
			aabb.min.y = _yB;
			aabb.max.y = _yA;
		}
		if ( _zA < _zB )
		{
			aabb.min.z = _zA;
			aabb.max.z = _zB;
		}
		else 
		{
			aabb.min.z = _zB;
			aabb.max.z = _zA;
		}
		return aabb;
	}
	
	// ---------------------------------------------------
	// Make a CGAABB
	// ---------------------------------------------------
	inline CGAABB CGAABBMake( const CGVector3D & _min, const CGVector3D & _max )
	{
		return CGAABBMake( _min.x, _min.y, _min.z, _max.x, _max.y, _max.z );
	}
	
	// ---------------------------------------------------
	// Scale a CGAABB
	// ---------------------------------------------------
	inline CGAABB CGAABBMakeScale( const CGAABB & _aabb, float _scale )
	{
		return CGAABBMake( _aabb.min.x*_scale, _aabb.min.y*_scale, _aabb.min.z*_scale, 
						   _aabb.max.x*_scale, _aabb.max.y*_scale, _aabb.max.z*_scale );
	}
	
	// ---------------------------------------------------
	// Make a CGAABB
	// ---------------------------------------------------
	inline CGAABB CGAABBMakeMerged( const CGAABB & _aabbA, const CGAABB & _aabbB )
	{
		return CGAABBMake( ( ( _aabbA.min.x > _aabbB.min.x ) ? _aabbB.min.x : _aabbA.min.x ),
						   ( ( _aabbA.min.y > _aabbB.min.y ) ? _aabbB.min.y : _aabbA.min.y ),
						   ( ( _aabbA.min.z > _aabbB.min.z ) ? _aabbB.min.z : _aabbA.min.z ),
						   ( ( _aabbA.max.x > _aabbB.max.x ) ? _aabbB.max.x : _aabbA.max.x ),
						   ( ( _aabbA.max.y > _aabbB.max.y ) ? _aabbB.max.y : _aabbA.max.y ),
						   ( ( _aabbA.max.z > _aabbB.max.z ) ? _aabbB.max.z : _aabbA.max.z ) );
	}
	
	// ---------------------------------------------------
	// Make a transformed CGAABB
	// ---------------------------------------------------
	inline CGAABB CGAABBMakeTransformed( const CGAABB & _aabb, const CGMatrix4x4 & _matrix )
	{
		CGAABB new_AABB = CGAABBMake( CGMatrix4x4TransformVector(_matrix, _aabb.min), CGMatrix4x4TransformVector(_matrix, _aabb.max) );
		
		CGVector3D corner = _aabb.min;
		
		corner.z = _aabb.max.z; // min min max
		CGAABBAddPoint( new_AABB, CGMatrix4x4TransformVector(_matrix, corner) );
		
		corner.y = _aabb.max.y; // min max max
		CGAABBAddPoint( new_AABB, CGMatrix4x4TransformVector(_matrix, corner) );
		
		corner.z = _aabb.min.z; // min max min
		CGAABBAddPoint( new_AABB, CGMatrix4x4TransformVector(_matrix, corner) );
		
		corner.x = _aabb.max.x; // max max min
		CGAABBAddPoint( new_AABB, CGMatrix4x4TransformVector(_matrix, corner) );
		
		corner.y = _aabb.min.y; // max min min
		CGAABBAddPoint( new_AABB, CGMatrix4x4TransformVector(_matrix, corner) );
		
		corner.z = _aabb.max.z; // max min max
		CGAABBAddPoint( new_AABB, CGMatrix4x4TransformVector(_matrix, corner) );
		
		return new_AABB;		
	};
	
#pragma mark ---------------------------------------------------------
#pragma mark End CGAABB Make Functions
#pragma mark ---------------------------------------------------------

};

#endif
