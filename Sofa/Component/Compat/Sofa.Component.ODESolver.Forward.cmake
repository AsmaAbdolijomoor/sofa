set(SOFAEXPLICITODESOLVER_SRC src/SofaExplicitOdeSolver)
set(SOFAGENERALEXPLICITODESOLVER_SRC src/SofaGeneralExplicitOdeSolver)
set(SOFAMISCSOLVER_SRC src/SofaMiscSolver)

list(APPEND HEADER_FILES
    ${SOFAEXPLICITODESOLVER_SRC}/EulerSolver.h
    ${SOFAGENERALEXPLICITODESOLVER_SRC}/CentralDifferenceSolver.h
    ${SOFAGENERALEXPLICITODESOLVER_SRC}/RungeKutta2Solver.h
    ${SOFAGENERALEXPLICITODESOLVER_SRC}/RungeKutta4Solver.h
    ${SOFAMISCSOLVER_SRC}/DampVelocitySolver.h
)