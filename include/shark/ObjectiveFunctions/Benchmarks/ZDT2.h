//===========================================================================
/*!
* \brief Multi-objective optimization benchmark function ZDT2
*
*  The function is described in
*
*  Eckart Zitzler, Kalyanmoy Deb, and Lothar Thiele. Comparison of
*  Multiobjective Evolutionary Algorithms: Empirical
*  Results. Evolutionary Computation 8(2):173-195, 2000
*
* <BR><HR>
* This file is part of Shark. This library is free software;
* you can redistribute it and/or modify it under the terms of the
* GNU General Public License as published by the Free Software
* Foundation; either version 3, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this library; if not, see <http://www.gnu.org/licenses/>.
* 
*/
//===========================================================================

#ifndef SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_ZDT2_H
#define SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_ZDT2_H

#include <shark/Core/AbstractBoxConstraintsProvider.h>
#include <shark/ObjectiveFunctions/AbstractMultiObjectiveFunction.h>
#include <shark/Core/Traits/ObjectiveFunctionTraits.h>
#include <shark/Core/SearchSpaces/VectorSpace.h>
namespace shark {
	/*! \brief Multi-objective optimization benchmark function ZDT2
	*
	*  The function is described in
	*
	*  Eckart Zitzler, Kalyanmoy Deb, and Lothar Thiele. Comparison of
	*  Multiobjective Evolutionary Algorithms: Empirical
	*  Results. Evolutionary Computation 8(2):173-195, 2000
	*/
	struct ZDT2 : 
		public AbstractMultiObjectiveFunction< VectorSpace<double> >,
		public TraitsBoxConstraintsProvider< VectorSpace<double>::PointType, ZDT2 > {
			typedef AbstractMultiObjectiveFunction< VectorSpace<double> > super;
			typedef TraitsBoxConstraintsProvider< VectorSpace<double>::PointType, ZDT2 > meta;

			typedef super::ResultType ResultType;
			typedef super::SearchPointType SearchPointType;

			ZDT2() : super( 2 ) {
				m_features |= CAN_PROPOSE_STARTING_POINT;
				m_features |= IS_CONSTRAINED_FEATURE;
				m_features |= CAN_PROVIDE_CLOSEST_FEASIBLE;
				m_name="ZDT2";
			}

			void init() {
			}

			ResultType eval( const SearchPointType & x ) const {
				m_evaluationCounter++;

				ResultType value( 2 );

				value[0] = x( 0 );

				double g, h, sum = 0.0;

				for (unsigned i = 1; i < numberOfVariables(); i++)
					sum += x(i);

				sum /= (numberOfVariables() - 1.0);

				g = 1.0 + (9.0 * sum);
				h = 1.0 - sqr((x( 0 ) / g));

				value[1] = g * h;

				return( value );
			}

			void proposeStartingPoint( SearchPointType & x ) const {
				meta::proposeStartingPoint( x, m_numberOfVariables );
			}

			bool isFeasible( const SearchPointType & v ) const {
				return( meta::isFeasible( v ) );
			}

			void closestFeasible( SearchPointType & v ) const {
				meta::closestFeasible( v );
			}

	};

	/**
	* \brief Specializes objective function traits for the function ZDT2.
	*/
	template<> 
	struct ObjectiveFunctionTraits<ZDT2> {

		static ZDT2::SearchPointType lowerBounds( unsigned int n ) {
			ZDT2::SearchPointType result( n, 0 );
			return( result );
		}

		static ZDT2::SearchPointType upperBounds( unsigned int n ) {
			ZDT2::SearchPointType result( n, 1 );
			return( result );
		}

	};

	ANNOUNCE_MULTI_OBJECTIVE_FUNCTION( ZDT2, shark::moo::RealValuedObjectiveFunctionFactory );
}
#endif