/**************************************************************************************************
*                                                                                                 *
* This file is part of HPIPM.                                                                     *
*                                                                                                 *
* HPIPM -- High-Performance Interior Point Method.                                                *
* Copyright (C) 2019 by Gianluca Frison.                                                          *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* The 2-Clause BSD License                                                                        *
*                                                                                                 *
* Redistribution and use in source and binary forms, with or without                              *
* modification, are permitted provided that the following conditions are met:                     *
*                                                                                                 *
* 1. Redistributions of source code must retain the above copyright notice, this                  *
*    list of conditions and the following disclaimer.                                             *
* 2. Redistributions in binary form must reproduce the above copyright notice,                    *
*    this list of conditions and the following disclaimer in the documentation                    *
*    and/or other materials provided with the distribution.                                       *
*                                                                                                 *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND                 *
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED                   *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                          *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR                 *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES                  *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;                    *
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND                     *
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                      *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                   *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                    *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/



int OCP_QP_IPM_ARG_STRSIZE()
	{
	return sizeof(struct OCP_QP_IPM_ARG);
	}



int OCP_QP_IPM_ARG_MEMSIZE(struct OCP_QP_DIM *dim)
	{

	return 0;

	}



void OCP_QP_IPM_ARG_CREATE(struct OCP_QP_DIM *dim, struct OCP_QP_IPM_ARG *arg, void *mem)
	{

#if 0
	// loop index
	int ii;

	// zero memory (to avoid corrupted memory like e.g. NaN)
	int memsize = OCP_QP_IPM_ARG_MEMSIZE(dim);
	int memsize_m8 = memsize/8; // sizeof(double) is 8
//	int memsize_r8 = memsize - 8*memsize_m8;
	double *double_ptr = mem;
	// XXX exploit that it is multiple of 64 bytes !!!!!
	for(ii=0; ii<memsize_m8-7; ii+=8)
		{
		double_ptr[ii+0] = 0.0;
		double_ptr[ii+1] = 0.0;
		double_ptr[ii+2] = 0.0;
		double_ptr[ii+3] = 0.0;
		double_ptr[ii+4] = 0.0;
		double_ptr[ii+5] = 0.0;
		double_ptr[ii+6] = 0.0;
		double_ptr[ii+7] = 0.0;
		}
//	for(; ii<memsize_m8; ii++)
//		{
//		double_ptr[ii] = 0.0;
//		}
//	char *char_ptr = (char *) (&double_ptr[ii]);
//	for(ii=0; ii<memsize_r8; ii++)
//		{
//		char_ptr[ii] = 0;
//		}
#endif

	arg->memsize = 0;

	return;

	}



void OCP_QP_IPM_ARG_SET_DEFAULT(enum HPIPM_MODE mode, struct OCP_QP_IPM_ARG *arg)
	{

	REAL mu0, alpha_min, res_g_max, res_b_max, res_d_max, res_m_max, reg_prim, lam_min, t_min;
	int iter_max, stat_max, pred_corr, cond_pred_corr, itref_pred_max, itref_corr_max, lq_fact, warm_start, abs_form, comp_res_exit, comp_res_pred, square_root_alg, comp_dual_sol;

	if(mode==SPEED_ABS)
		{
		mu0 = 1e1;
		alpha_min = 1e-12;
		res_g_max = 1e0; // not used
		res_b_max = 1e0; // not used
		res_d_max = 1e0; // not used
		res_m_max = 1e-8;
		iter_max = 15;
		stat_max = 15;
		pred_corr = 1;
		cond_pred_corr = 1;
		itref_pred_max = 0; // not used
		itref_corr_max = 0; // not used
		reg_prim = 1e-15;
		square_root_alg = 1;
		lq_fact = 0; // not used
		lam_min = 1e-16;
		t_min = 1e-16;
		warm_start = 0;
		abs_form = 1;
		comp_dual_sol = 0;
		comp_res_exit = 0;
		comp_res_pred = 0;
		mode = mode;
		}
	else if(mode==SPEED)
		{
		mu0 = 1e1;
		alpha_min = 1e-12;
		res_g_max = 1e-6;
		res_b_max = 1e-8;
		res_d_max = 1e-8;
		res_m_max = 1e-8;
		iter_max = 15;
		stat_max = 15;
		pred_corr = 1;
		cond_pred_corr = 1;
		itref_pred_max = 0;
		itref_corr_max = 0;
		reg_prim = 1e-15;
		square_root_alg = 1;
		lq_fact = 0;
		lam_min = 1e-16;
		t_min = 1e-16;
		warm_start = 0;
		abs_form = 0;
		comp_dual_sol = 1;
		comp_res_exit = 1;
		comp_res_pred = 1;
		mode = mode;
		}
	else if(mode==BALANCE)
		{
		mu0 = 1e1;
		alpha_min = 1e-12;
		res_g_max = 1e-6;
		res_b_max = 1e-8;
		res_d_max = 1e-8;
		res_m_max = 1e-8;
		iter_max = 30;
		stat_max = 30;
		pred_corr = 1;
		cond_pred_corr = 1;
		itref_pred_max = 0;
		itref_corr_max = 2;
		reg_prim = 1e-15;
		square_root_alg = 1;
		lq_fact = 1;
		lam_min = 1e-16;
		t_min = 1e-16;
		warm_start = 0;
		abs_form = 0;
		comp_dual_sol = 1;
		comp_res_exit = 1;
		comp_res_pred = 1;
		mode = mode;
		}
	else if(mode==ROBUST)
		{
		mu0 = 1e2;
		alpha_min = 1e-12;
		res_g_max = 1e-6;
		res_b_max = 1e-8;
		res_d_max = 1e-8;
		res_m_max = 1e-8;
		iter_max = 100;
		stat_max = 100;
		pred_corr = 1;
		cond_pred_corr = 1;
		itref_pred_max = 0;
		itref_corr_max = 4;
		reg_prim = 1e-15;
		square_root_alg = 1;
		lq_fact = 2;
		lam_min = 1e-16;
		t_min = 1e-16;
		warm_start = 0;
		abs_form = 0;
		comp_dual_sol = 1;
		comp_res_exit = 1;
		comp_res_pred = 1;
		mode = mode;
		}
	else
		{
		printf("\nerror: OCP_QP_IPM_ARG_SET_DEFAULT: wrong set default mode\n");
		exit(1);
		}

	// use individual setters when available
	OCP_QP_IPM_ARG_SET_MU0(&mu0, arg);
	OCP_QP_IPM_ARG_SET_ALPHA_MIN(&alpha_min, arg);
	OCP_QP_IPM_ARG_SET_TOL_STAT(&res_g_max, arg);
	OCP_QP_IPM_ARG_SET_TOL_EQ(&res_b_max, arg);
	OCP_QP_IPM_ARG_SET_TOL_INEQ(&res_d_max, arg);
	OCP_QP_IPM_ARG_SET_TOL_COMP(&res_m_max, arg);
	OCP_QP_IPM_ARG_SET_ITER_MAX(&iter_max, arg);
	arg->stat_max = stat_max;
	OCP_QP_IPM_ARG_SET_PRED_CORR(&pred_corr, arg);
	OCP_QP_IPM_ARG_SET_COND_PRED_CORR(&cond_pred_corr, arg);
	OCP_QP_IPM_ARG_SET_RIC_ALG(&square_root_alg, arg);
	arg->itref_pred_max = itref_pred_max;
	arg->itref_corr_max = itref_corr_max;
	OCP_QP_IPM_ARG_SET_REG_PRIM(&reg_prim, arg);
	arg->lq_fact = lq_fact;
	OCP_QP_IPM_ARG_SET_LAM_MIN(&lam_min, arg);
	OCP_QP_IPM_ARG_SET_T_MIN(&t_min, arg);
	OCP_QP_IPM_ARG_SET_WARM_START(&warm_start, arg);
	arg->abs_form = abs_form;
	OCP_QP_IPM_ARG_SET_COMP_RES_PRED(&comp_res_pred, arg);
	OCP_QP_IPM_ARG_SET_COMP_RES_EXIT(&comp_res_pred, arg);
	arg->mode = mode;

	return;

	}



void OCP_QP_IPM_ARG_SET(char *field, void *value, struct OCP_QP_IPM_ARG *arg)
	{
	if(hpipm_strcmp(field, "iter_max")) 
		{
		OCP_QP_IPM_ARG_SET_ITER_MAX(value, arg);
		}
	else if(hpipm_strcmp(field, "alpha_min")) 
		{
		OCP_QP_IPM_ARG_SET_ALPHA_MIN(value, arg);
		}
	else if(hpipm_strcmp(field, "mu0")) 
		{
		OCP_QP_IPM_ARG_SET_MU0(value, arg);
		}
	else if(hpipm_strcmp(field, "tol_stat")) 
		{
		OCP_QP_IPM_ARG_SET_TOL_STAT(value, arg);
		}
	else if(hpipm_strcmp(field, "tol_eq")) 
		{
		OCP_QP_IPM_ARG_SET_TOL_EQ(value, arg);
		}
	else if(hpipm_strcmp(field, "tol_ineq")) 
		{
		OCP_QP_IPM_ARG_SET_TOL_INEQ(value, arg);
		}
	else if(hpipm_strcmp(field, "tol_comp")) 
		{
		OCP_QP_IPM_ARG_SET_TOL_COMP(value, arg);
		}
	else if(hpipm_strcmp(field, "reg_prim")) 
		{
		OCP_QP_IPM_ARG_SET_REG_PRIM(value, arg);
		}
	else if(hpipm_strcmp(field, "warm_start")) 
		{
		OCP_QP_IPM_ARG_SET_WARM_START(value, arg);
		}
	else if(hpipm_strcmp(field, "pred_corr")) 
		{
		OCP_QP_IPM_ARG_SET_PRED_CORR(value, arg);
		}
	else if(hpipm_strcmp(field, "cond_pred_corr")) 
		{
		OCP_QP_IPM_ARG_SET_COND_PRED_CORR(value, arg);
		}
	else if(hpipm_strcmp(field, "ric_alg")) 
		{
		OCP_QP_IPM_ARG_SET_RIC_ALG(value, arg);
		}
	else if(hpipm_strcmp(field, "comp_res_exit")) 
		{
		OCP_QP_IPM_ARG_SET_COMP_RES_EXIT(value, arg);
		}
	else if(hpipm_strcmp(field, "comp_res_pred")) 
		{
		OCP_QP_IPM_ARG_SET_COMP_RES_PRED(value, arg);
		}
	else if(hpipm_strcmp(field, "lam_min")) 
		{
		OCP_QP_IPM_ARG_SET_LAM_MIN(value, arg);
		}
	else if(hpipm_strcmp(field, "t_min")) 
		{
		OCP_QP_IPM_ARG_SET_T_MIN(value, arg);
		}
	else
		{
		printf("error: OCP_QP_IPM_ARG_SET: wrong field %s\n", field);
		exit(1);	
		}
	return;
	}



void OCP_QP_IPM_ARG_SET_ITER_MAX(int *iter_max, struct OCP_QP_IPM_ARG *arg)
	{
	arg->iter_max = *iter_max;
	return;
	}



void OCP_QP_IPM_ARG_SET_ALPHA_MIN(REAL *alpha_min, struct OCP_QP_IPM_ARG *arg)
	{
	arg->alpha_min = *alpha_min;
	return;
	}



void OCP_QP_IPM_ARG_SET_MU0(REAL *mu0, struct OCP_QP_IPM_ARG *arg)
	{
	arg->mu0 = *mu0;
	return;
	}



void OCP_QP_IPM_ARG_SET_TOL_STAT(REAL *tol_stat, struct OCP_QP_IPM_ARG *arg)
	{
	arg->res_g_max = *tol_stat;
	return;
	}



void OCP_QP_IPM_ARG_SET_TOL_EQ(REAL *tol_eq, struct OCP_QP_IPM_ARG *arg)
	{
	arg->res_b_max = *tol_eq;
	return;
	}



void OCP_QP_IPM_ARG_SET_TOL_INEQ(REAL *tol_ineq, struct OCP_QP_IPM_ARG *arg)
	{
	arg->res_d_max = *tol_ineq;
	return;
	}



void OCP_QP_IPM_ARG_SET_TOL_COMP(REAL *tol_comp, struct OCP_QP_IPM_ARG *arg)
	{
	arg->res_m_max = *tol_comp;
	return;
	}



void OCP_QP_IPM_ARG_SET_REG_PRIM(REAL *reg, struct OCP_QP_IPM_ARG *arg)
	{
	arg->reg_prim = *reg;
	return;
	}



void OCP_QP_IPM_ARG_SET_WARM_START(int *warm_start, struct OCP_QP_IPM_ARG *arg)
	{
	arg->warm_start = *warm_start;
	return;
	}



void OCP_QP_IPM_ARG_SET_PRED_CORR(int *pred_corr, struct OCP_QP_IPM_ARG *arg)
	{
	arg->pred_corr = *pred_corr;
	return;
	}



void OCP_QP_IPM_ARG_SET_COND_PRED_CORR(int *value, struct OCP_QP_IPM_ARG *arg)
	{
	arg->cond_pred_corr = *value;
	return;
	}



void OCP_QP_IPM_ARG_SET_RIC_ALG(int *ric_alg, struct OCP_QP_IPM_ARG *arg)
	{
	arg->square_root_alg = *ric_alg;
	return;
	}



void OCP_QP_IPM_ARG_SET_COMP_RES_EXIT(int *comp_res_exit, struct OCP_QP_IPM_ARG *arg)
	{
	arg->comp_res_exit = *comp_res_exit;
	if(*comp_res_exit!=0)
		arg->comp_dual_sol = 1;
	return;
	}



void OCP_QP_IPM_ARG_SET_COMP_RES_PRED(int *comp_res_pred, struct OCP_QP_IPM_ARG *arg)
	{
	arg->comp_res_pred = *comp_res_pred;
	return;
	}



void OCP_QP_IPM_ARG_SET_LAM_MIN(REAL *value, struct OCP_QP_IPM_ARG *arg)
	{
	arg->lam_min = *value;
	return;
	}



void OCP_QP_IPM_ARG_SET_T_MIN(REAL *value, struct OCP_QP_IPM_ARG *arg)
	{
	arg->t_min = *value;
	return;
	}



int OCP_QP_IPM_WS_STRSIZE()
	{
	return sizeof(struct OCP_QP_IPM_WS);
	}



int OCP_QP_IPM_WS_MEMSIZE(struct OCP_QP_DIM *dim, struct OCP_QP_IPM_ARG *arg)
	{

	// stat_max is at least as big as iter_max
	if(arg->iter_max > arg->stat_max)
		arg->stat_max = arg->iter_max;

	// loop index
	int ii;

	// extract ocp qp size
	int N = dim->N;
	int *nx = dim->nx;
	int *nu = dim->nu;
	int *nb = dim->nb;
	int *ng = dim->ng;
	int *ns = dim->ns;

	// compute core qp size and max size
	int nvt = 0;
	int net = 0;
	int nct = 0;
	int nxM = 0;
	int nuM = 0;
	int nbM = 0;
	int ngM = 0;
	int nsM = 0;
	for(ii=0; ii<N; ii++)
		{
		nvt += nx[ii]+nu[ii]+2*ns[ii];
		net += nx[ii+1];
		nct += 2*nb[ii]+2*ng[ii]+2*ns[ii];
		nxM = nx[ii]>nxM ? nx[ii] : nxM;
		nuM = nu[ii]>nuM ? nu[ii] : nuM;
		nbM = nb[ii]>nbM ? nb[ii] : nbM;
		ngM = ng[ii]>ngM ? ng[ii] : ngM;
		nsM = ns[ii]>nsM ? ns[ii] : nsM;
		}
	nvt += nx[ii]+nu[ii]+2*ns[ii];
	nct += 2*nb[ii]+2*ng[ii]+2*ns[ii];
	nxM = nx[ii]>nxM ? nx[ii] : nxM;
	nuM = nu[ii]>nuM ? nu[ii] : nuM;
	nbM = nb[ii]>nbM ? nb[ii] : nbM;
	ngM = ng[ii]>ngM ? ng[ii] : ngM;
	nsM = ns[ii]>nsM ? ns[ii] : nsM;

	int size = 0;

	size += 1*sizeof(struct CORE_QP_IPM_WORKSPACE);
	size += 1*MEMSIZE_CORE_QP_IPM(nvt, net, nct);

	size += 1*sizeof(struct OCP_QP_RES_WS); // res_workspace

	size += 2*sizeof(struct OCP_QP); // qp_step qp_itref

	size += 2*sizeof(struct OCP_QP_SOL); // sol_step sol_itref
	size += 1*OCP_QP_SOL_MEMSIZE(dim); // sol_itref

	size += 2*sizeof(struct OCP_QP_RES); // res res_itref
	size += 1*OCP_QP_RES_MEMSIZE(dim); // res_itref

	size += 9*(N+1)*sizeof(struct STRVEC); // res_g res_d res_m Gamma gamma Zs_inv sol_step(v,lam,t)
	size += 3*N*sizeof(struct STRVEC); // res_b Pb sol_step(pi) 
	size += 10*sizeof(struct STRVEC); // tmp_nxM (4+2)*tmp_nbgM (1+1)*tmp_nsM tmp_m

	size += 1*(N+1)*sizeof(struct STRMAT); // L
	if(!arg->square_root_alg)
		{
		size += 1*(N+1)*sizeof(struct STRMAT); // P
		size += 1*sizeof(struct STRMAT); // Ls
		}
	else
		{
		size += 2*sizeof(struct STRMAT); // P
		}
	if(arg->lq_fact>0)
		{
		size += 1*(N+1)*sizeof(struct STRMAT); // Lh
		}
	size += 2*sizeof(struct STRMAT); // AL
	if(arg->lq_fact>0)
		{
		size += 1*sizeof(struct STRMAT); // lq0
		}

	size += 1*SIZE_STRVEC(nxM); // tmp_nxM
	size += 4*SIZE_STRVEC(nbM+ngM); // tmp_nbgM
	size += 1*SIZE_STRVEC(nsM); // tmp_nsM
	for(ii=0; ii<N; ii++) size += 1*SIZE_STRVEC(nx[ii+1]); // Pb
	for(ii=0; ii<=N; ii++) size += 1*SIZE_STRVEC(2*ns[ii]); // Zs_inv

	for(ii=0; ii<=N; ii++) size += 1*SIZE_STRMAT(nu[ii]+nx[ii]+1, nu[ii]+nx[ii]); // L
	if(!arg->square_root_alg)
		{
		for(ii=0; ii<=N; ii++) size += 1*SIZE_STRMAT(nx[ii]+1, nx[ii]); // P
		size += 1*SIZE_STRMAT(nxM+1, nuM); // Ls
		}
	else
		{
		size += 2*SIZE_STRMAT(nxM, nxM); // P
		}
	if(arg->lq_fact>0)
		{
		for(ii=0; ii<=N; ii++) size += 1*SIZE_STRMAT(nu[ii]+nx[ii]+1, nu[ii]+nx[ii]); // Lh
		}
	size += 2*SIZE_STRMAT(nuM+nxM+1, nxM+ngM); // AL
	if(arg->lq_fact>0)
		{
		size += 1*SIZE_STRMAT(nuM+nxM, 2*nuM+3*nxM+ngM); // lq0
		}
	size += 1*SIZE_STRVEC(nct); // tmp_m

	if(arg->lq_fact>0)
		{
		size += 1*GELQF_WORKSIZE(nuM+nxM, 2*nuM+3*nxM+ngM); // lq_work0
		}

	int stat_m = 11;
	size += stat_m*(1+arg->stat_max)*sizeof(REAL); // stat

	size += (N+1)*sizeof(int); // use_hess_fact

	size = (size+63)/64*64; // make multiple of typical cache line size
	size += 1*64; // align once to typical cache line size

	return size;

	}



void OCP_QP_IPM_WS_CREATE(struct OCP_QP_DIM *dim, struct OCP_QP_IPM_ARG *arg, struct OCP_QP_IPM_WS *workspace, void *mem)
	{

	// loop index
	int ii;

	// zero memory (to avoid corrupted memory like e.g. NaN)
	int memsize = OCP_QP_IPM_WS_MEMSIZE(dim, arg);
	int memsize_m8 = memsize/8; // sizeof(double) is 8
//	int memsize_r8 = memsize - 8*memsize_m8;
	double *double_ptr = mem;
	// XXX exploit that it is multiple of 64 bytes !!!!!
	for(ii=0; ii<memsize_m8-7; ii+=8)
		{
		double_ptr[ii+0] = 0.0;
		double_ptr[ii+1] = 0.0;
		double_ptr[ii+2] = 0.0;
		double_ptr[ii+3] = 0.0;
		double_ptr[ii+4] = 0.0;
		double_ptr[ii+5] = 0.0;
		double_ptr[ii+6] = 0.0;
		double_ptr[ii+7] = 0.0;
		}
//	for(; ii<memsize_m8; ii++)
//		{
//		double_ptr[ii] = 0.0;
//		}
//	char *char_ptr = (char *) (&double_ptr[ii]);
//	for(ii=0; ii<memsize_r8; ii++)
//		{
//		char_ptr[ii] = 0;
//		}

	// extract ocp qp size
	int N = dim->N;
	int *nx = dim->nx;
	int *nu = dim->nu;
	int *nb = dim->nb;
	int *ng = dim->ng;
	int *ns = dim->ns;


	// compute core qp size and max size
	int nvt = 0;
	int net = 0;
	int nct = 0;
	int nxM = 0;
	int nuM = 0;
	int nbM = 0;
	int ngM = 0;
	int nsM = 0;
	for(ii=0; ii<N; ii++)
		{
		nvt += nx[ii]+nu[ii]+2*ns[ii];
		net += nx[ii+1];
		nct += 2*nb[ii]+2*ng[ii]+2*ns[ii];
		nxM = nx[ii]>nxM ? nx[ii] : nxM;
		nuM = nu[ii]>nuM ? nu[ii] : nuM;
		nbM = nb[ii]>nbM ? nb[ii] : nbM;
		ngM = ng[ii]>ngM ? ng[ii] : ngM;
		nsM = ns[ii]>nsM ? ns[ii] : nsM;
		}
	nvt += nx[ii]+nu[ii]+2*ns[ii];
	nct += 2*nb[ii]+2*ng[ii]+2*ns[ii];
	nxM = nx[ii]>nxM ? nx[ii] : nxM;
	nuM = nu[ii]>nuM ? nu[ii] : nuM;
	nbM = nb[ii]>nbM ? nb[ii] : nbM;
	ngM = ng[ii]>ngM ? ng[ii] : ngM;
	nsM = ns[ii]>nsM ? ns[ii] : nsM;


	// core struct
	struct CORE_QP_IPM_WORKSPACE *sr_ptr = mem;

	// core workspace
	workspace->core_workspace = sr_ptr;
	sr_ptr += 1;
	struct CORE_QP_IPM_WORKSPACE *cws = workspace->core_workspace;


	// res struct
	struct OCP_QP_RES *res_ptr = (struct OCP_QP_RES *) sr_ptr;
	workspace->res = res_ptr;
	res_ptr += 1;
	workspace->res_itref = res_ptr;
	res_ptr += 1;


	// res workspace struct
	struct OCP_QP_RES_WS *res_ws_ptr = (struct OCP_QP_RES_WS *) res_ptr;
	workspace->res_workspace = res_ws_ptr;
	res_ws_ptr += 1;


	// qp sol struct
	struct OCP_QP_SOL *qp_sol_ptr = (struct OCP_QP_SOL *) res_ws_ptr;

	workspace->sol_step = qp_sol_ptr;
	qp_sol_ptr += 1;
	workspace->sol_itref = qp_sol_ptr;
	qp_sol_ptr += 1;


	// qp struct
	struct OCP_QP *qp_ptr = (struct OCP_QP *) qp_sol_ptr;

	workspace->qp_step = qp_ptr;
	qp_ptr += 1;
	workspace->qp_itref = qp_ptr;
	qp_ptr += 1;


	// matrix struct
	struct STRMAT *sm_ptr = (struct STRMAT *) qp_ptr;

	workspace->L = sm_ptr;
	sm_ptr += N+1;
	if(!arg->square_root_alg)
		{
		workspace->P = sm_ptr;
		sm_ptr += N+1;
		workspace->Ls = sm_ptr;
		sm_ptr += 1;
		}
	else
		{
		workspace->P = sm_ptr;
		sm_ptr += 2;
		}
	if(arg->lq_fact>0)
		{
		workspace->Lh = sm_ptr;
		sm_ptr += N+1;
		}
	workspace->AL = sm_ptr;
	sm_ptr += 2;
	if(arg->lq_fact>0)
		{
		workspace->lq0 = sm_ptr;
		sm_ptr += 1;
		}


	// vector struct
	struct STRVEC *sv_ptr = (struct STRVEC *) sm_ptr;

	workspace->sol_step->ux = sv_ptr;
	sv_ptr += N+1;
	workspace->sol_step->pi = sv_ptr;
	sv_ptr += N;
	workspace->sol_step->lam = sv_ptr;
	sv_ptr += N+1;
	workspace->sol_step->t = sv_ptr;
	sv_ptr += N+1;
	workspace->res->res_g = sv_ptr;
	sv_ptr += N+1;
	workspace->res->res_b = sv_ptr;
	sv_ptr += N;
	workspace->res->res_d = sv_ptr;
	sv_ptr += N+1;
	workspace->res->res_m = sv_ptr;
	sv_ptr += N+1;
	workspace->Gamma = sv_ptr;
	sv_ptr += N+1;
	workspace->gamma = sv_ptr;
	sv_ptr += N+1;
	workspace->Pb = sv_ptr;
	sv_ptr += N;
	workspace->Zs_inv = sv_ptr;
	sv_ptr += N+1;
	workspace->tmp_nxM = sv_ptr;
	sv_ptr += 1;
	workspace->tmp_nbgM = sv_ptr;
	sv_ptr += 4;
	workspace->res_workspace->tmp_nbgM = sv_ptr;
	sv_ptr += 2;
	workspace->tmp_nsM = sv_ptr;
	sv_ptr += 1;
	workspace->res_workspace->tmp_nsM = sv_ptr;
	sv_ptr += 1;
	workspace->tmp_m = sv_ptr;
	sv_ptr += 1;


	// double/float stuff
	REAL *d_ptr = (REAL *) sv_ptr;

	workspace->stat = d_ptr;
	int stat_m = 11;
	d_ptr += stat_m*(1+arg->stat_max);

	// int stuff
	int *i_ptr = (int *) d_ptr;

	workspace->use_hess_fact = i_ptr;
	i_ptr += N+1;

	// align to typicl cache line size
	size_t s_ptr = (size_t) i_ptr;
	s_ptr = (s_ptr+63)/64*64;


	// void stuf
	char *c_ptr = (char *) s_ptr;

	OCP_QP_SOL_CREATE(dim, workspace->sol_itref, c_ptr);
	c_ptr += workspace->sol_itref->memsize;

	OCP_QP_RES_CREATE(dim, workspace->res_itref, c_ptr);
	c_ptr += workspace->res_itref->memsize;

	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRMAT(nu[ii]+nx[ii]+1, nu[ii]+nx[ii], workspace->L+ii, c_ptr);
		c_ptr += (workspace->L+ii)->memsize;
		}
	if(!arg->square_root_alg)
		{
		for(ii=0; ii<=N; ii++)
			{
			CREATE_STRMAT(nx[ii]+1, nx[ii], workspace->P+ii, c_ptr);
			c_ptr += (workspace->P+ii)->memsize;
			}
		CREATE_STRMAT(nxM+1, nuM, workspace->Ls, c_ptr);
		c_ptr += (workspace->Ls)->memsize;
		}
	else
		{
		CREATE_STRMAT(nxM, nxM, workspace->P+0, c_ptr);
		c_ptr += (workspace->P+0)->memsize;
		CREATE_STRMAT(nxM, nxM, workspace->P+1, c_ptr);
		c_ptr += (workspace->P+1)->memsize;
		}

	if(arg->lq_fact>0)
		{
		for(ii=0; ii<=N; ii++)
			{
			CREATE_STRMAT(nu[ii]+nx[ii]+1, nu[ii]+nx[ii], workspace->Lh+ii, c_ptr);
			c_ptr += (workspace->Lh+ii)->memsize;
			}
		}

	CREATE_STRMAT(nuM+nxM+1, nxM+ngM, workspace->AL+0, c_ptr);
	c_ptr += (workspace->AL+0)->memsize;

	CREATE_STRMAT(nuM+nxM+1, nxM+ngM, workspace->AL+1, c_ptr);
	c_ptr += (workspace->AL+1)->memsize;

	if(arg->lq_fact>0)
		{
		CREATE_STRMAT(nuM+nxM, 2*nuM+3*nxM+ngM, workspace->lq0, c_ptr);
		c_ptr += (workspace->lq0)->memsize;
		}

	for(ii=0; ii<N; ii++)
		{
		CREATE_STRVEC(nx[ii+1], workspace->Pb+ii, c_ptr);
		c_ptr += (workspace->Pb+ii)->memsize;
		}

	for(ii=0; ii<N+1; ii++)
		{
		CREATE_STRVEC(2*ns[ii], workspace->Zs_inv+ii, c_ptr);
		c_ptr += (workspace->Zs_inv+ii)->memsize;
		}

	CREATE_STRVEC(nxM, workspace->tmp_nxM, c_ptr);
	c_ptr += workspace->tmp_nxM->memsize;

	CREATE_STRVEC(nbM+ngM, workspace->tmp_nbgM+0, c_ptr);
	CREATE_STRVEC(nbM+ngM, workspace->res_workspace->tmp_nbgM+0, c_ptr);
	c_ptr += (workspace->tmp_nbgM+0)->memsize;

	CREATE_STRVEC(nbM+ngM, workspace->tmp_nbgM+1, c_ptr);
	CREATE_STRVEC(nbM+ngM, workspace->res_workspace->tmp_nbgM+1, c_ptr);
	c_ptr += (workspace->tmp_nbgM+1)->memsize;

	CREATE_STRVEC(nbM+ngM, workspace->tmp_nbgM+2, c_ptr);
	c_ptr += (workspace->tmp_nbgM+2)->memsize;

	CREATE_STRVEC(nbM+ngM, workspace->tmp_nbgM+3, c_ptr);
	c_ptr += (workspace->tmp_nbgM+3)->memsize;

	CREATE_STRVEC(nsM, workspace->tmp_nsM+0, c_ptr);
	CREATE_STRVEC(nsM, workspace->res_workspace->tmp_nsM+0, c_ptr);
	c_ptr += (workspace->tmp_nsM+0)->memsize;

	CREATE_STRVEC(nct, workspace->tmp_m, c_ptr);
	c_ptr += SIZE_STRVEC(nct);

	CREATE_CORE_QP_IPM(nvt, net, nct, cws, c_ptr);
	c_ptr += workspace->core_workspace->memsize;

	if(arg->lq_fact>0)
		{
		workspace->lq_work0 = c_ptr;
		c_ptr += GELQF_WORKSIZE(nuM+nxM, 2*nuM+3*nxM+ngM);
		}


	// alias members of workspace and core_workspace
	//
	c_ptr = (char *) cws->dv;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(nu[ii]+nx[ii]+2*ns[ii], workspace->sol_step->ux+ii, c_ptr);
		c_ptr += (nu[ii]+nx[ii])*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->dpi;
	for(ii=0; ii<N; ii++)
		{
		CREATE_STRVEC(nx[ii+1], workspace->sol_step->pi+ii, c_ptr);
		c_ptr += (nx[ii+1])*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->dlam;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(2*nb[ii]+2*ng[ii]+2*ns[ii], workspace->sol_step->lam+ii, c_ptr);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->dt;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(2*nb[ii]+2*ng[ii]+2*ns[ii], workspace->sol_step->t+ii, c_ptr);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->res_g;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(nu[ii]+nx[ii]+2*ns[ii], workspace->res->res_g+ii, c_ptr);
		c_ptr += (nu[ii]+nx[ii])*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->res_b;
	for(ii=0; ii<N; ii++)
		{
		CREATE_STRVEC(nx[ii+1], workspace->res->res_b+ii, c_ptr);
		c_ptr += (nx[ii+1])*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->res_d;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(2*nb[ii]+2*ng[ii]+2*ns[ii], workspace->res->res_d+ii, c_ptr);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->res_m;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(2*nb[ii]+2*ng[ii]+2*ns[ii], workspace->res->res_m+ii, c_ptr);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->Gamma;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(2*nb[ii]+2*ng[ii]+2*ns[ii], workspace->Gamma+ii, c_ptr);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}
	//
	c_ptr = (char *) cws->gamma;
	for(ii=0; ii<=N; ii++)
		{
		CREATE_STRVEC(2*nb[ii]+2*ng[ii]+2*ns[ii], workspace->gamma+ii, c_ptr);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += nb[ii]*sizeof(REAL);
		c_ptr += ng[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		c_ptr += ns[ii]*sizeof(REAL);
		}


	workspace->res->dim = dim;

	workspace->stat_max = arg->stat_max;
	workspace->stat_m = stat_m;

	for(ii=0; ii<=N; ii++)
		workspace->use_hess_fact[ii] = 0;
	
	workspace->use_Pb = 0;

	// cache stuff
	workspace->dim = dim;
	workspace->square_root_alg = arg->square_root_alg;
	workspace->lq_fact = arg->lq_fact;

	workspace->memsize = memsize; //OCP_QP_IPM_WS_MEMSIZE(dim, arg);


#if defined(RUNTIME_CHECKS)
	if(c_ptr > ((char *) mem) + workspace->memsize)
		{
		printf("\nCreate_ocp_qp_ipm: outside memory bounds!\n\n");
		exit(1);
		}
#endif

	return;

	}


void OCP_QP_IPM_GET(char *field, struct OCP_QP_IPM_WS *ws, void *value)
	{
	if(hpipm_strcmp(field, "status"))
		{ 
		OCP_QP_IPM_GET_STATUS(ws, value);
		}
	else if(hpipm_strcmp(field, "iter"))
		{ 
		OCP_QP_IPM_GET_ITER(ws, value);
		}
	else if(hpipm_strcmp(field, "max_res_stat"))
		{ 
		OCP_QP_IPM_GET_MAX_RES_STAT(ws, value);
		}
	else if(hpipm_strcmp(field, "max_res_eq"))
		{ 
		OCP_QP_IPM_GET_MAX_RES_EQ(ws, value);
		}
	else if(hpipm_strcmp(field, "max_res_ineq"))
		{ 
		OCP_QP_IPM_GET_MAX_RES_INEQ(ws, value);
		}
	else if(hpipm_strcmp(field, "max_res_comp"))
		{ 
		OCP_QP_IPM_GET_MAX_RES_COMP(ws, value);
		}
	else if(hpipm_strcmp(field, "stat"))
		{ 
		OCP_QP_IPM_GET_STAT(ws, value);
		}
	else if(hpipm_strcmp(field, "stat_m"))
		{ 
		OCP_QP_IPM_GET_STAT_M(ws, value);
		}
	else 
		{
		printf("error: OCP_QP_IPM_GET: wrong field %s\n", field);
		exit(1);
		}
	return;
	}



void OCP_QP_IPM_GET_STATUS(struct OCP_QP_IPM_WS *ws, int *status)
	{
	*status = ws->status;
	return;
	}



void OCP_QP_IPM_GET_ITER(struct OCP_QP_IPM_WS *ws, int *iter)
	{
	*iter = ws->iter;
	return;
	}



void OCP_QP_IPM_GET_MAX_RES_STAT(struct OCP_QP_IPM_WS *ws, REAL *res_stat)
	{
	*res_stat = ws->res->res_max[0];
	return;
	}



void OCP_QP_IPM_GET_MAX_RES_EQ(struct OCP_QP_IPM_WS *ws, REAL *res_eq)
	{
	*res_eq = ws->res->res_max[1];
	return;
	}



void OCP_QP_IPM_GET_MAX_RES_INEQ(struct OCP_QP_IPM_WS *ws, REAL *res_ineq)
	{
	*res_ineq = ws->res->res_max[2];
	return;
	}



void OCP_QP_IPM_GET_MAX_RES_COMP(struct OCP_QP_IPM_WS *ws, REAL *res_comp)
	{
	*res_comp = ws->res->res_max[3];
	return;
	}



void OCP_QP_IPM_GET_STAT(struct OCP_QP_IPM_WS *ws, REAL **stat)
	{
	*stat = ws->stat;
	}



void OCP_QP_IPM_GET_STAT_M(struct OCP_QP_IPM_WS *ws, int *stat_m)
	{
	*stat_m = ws->stat_m;
	}



void OCP_QP_IPM_GET_RIC_LR(int stage, struct OCP_QP_IPM_WS *ws, REAL *Lr)
	{
	int *nu = ws->dim->nu;

	int nu0 = nu[stage];

	UNPACK_MAT(nu0, nu0, ws->L+stage, 0, 0, Lr, nu0);
	}



void OCP_QP_IPM_GET_RIC_LS(int stage, struct OCP_QP_IPM_WS *ws, REAL *Ls)
	{
	int *nu = ws->dim->nu;
	int *nx = ws->dim->nx;

	int nu0 = nu[stage];
	int nx0 = nx[stage];

	UNPACK_MAT(nx0, nu0, ws->L+stage, nu0, 0, Ls, nx0);
	}



void OCP_QP_IPM_GET_RIC_P(int stage, struct OCP_QP_IPM_WS *ws, REAL *P)
	{
	int *nu = ws->dim->nu;
	int *nx = ws->dim->nx;

	int nu0 = nu[stage];
	int nx0 = nx[stage];

	if(ws->square_root_alg)
		{
		GESE(nx0, nx0, 0.0, ws->P+0, 0, 0);
		TRCP_L(nx0, ws->L+stage, nu0, nu0, ws->P+0, 0, 0);
		SYRK_LN(nx0, nx0, 1.0, ws->P+0, 0, 0, ws->P+0, 0, 0, 0.0, ws->P+1, 0, 0, ws->P+1, 0, 0); // TODO lauum
		TRTR_L(nx0, ws->P+1, 0, 0, ws->P+1, 0, 0);
		UNPACK_MAT(nx0, nx0, ws->P+1, 0, 0, P, nx0);
		}
	else
		{
		UNPACK_MAT(nx0, nx0, ws->P+stage, 0, 0, P, nx0);
		}
	}



// XXX valid only in the unconstrained case !!!
void OCP_QP_IPM_GET_RIC_LR_VEC(int stage, struct OCP_QP_IPM_WS *ws, REAL *lr)
	{
	int *nu = ws->dim->nu;
	int *nx = ws->dim->nx;

	int nu0 = nu[stage];
	int nx0 = nx[stage];

	UNPACK_MAT(1, nu0, ws->L+stage, nu0+nx0, 0, lr, 1);
	}



// XXX valid only in the unconstrained case !!!
void OCP_QP_IPM_GET_RIC_P_VEC(int stage, struct OCP_QP_IPM_WS *ws, REAL *p)
	{
	int *nu = ws->dim->nu;
	int *nx = ws->dim->nx;

	int nu0 = nu[stage];
	int nx0 = nx[stage];

	if(ws->square_root_alg)
		{
		ROWEX(nx0, 1.0, ws->L+stage, nu0+nx0, nu0, ws->tmp_nxM, 0);
		TRMV_LNN(nx0, nx0, ws->L+stage, nu0, nu0, ws->tmp_nxM, 0, ws->tmp_nxM, 0);
		UNPACK_VEC(nx0, ws->tmp_nxM, 0, p);
		}
	else
		{
		UNPACK_MAT(1, nx0, ws->P+stage, nx0, 0, p, 1);
		}
	}



// with warm_start==2 also init dual variables
void OCP_QP_INIT_VAR(struct OCP_QP *qp, struct OCP_QP_SOL *qp_sol, struct OCP_QP_IPM_ARG *arg, struct OCP_QP_IPM_WS *ws)
	{

//	struct CORE_QP_IPM_WORKSPACE *cws = ws->core_workspace;
	
	// loop index
	int ii, jj;

	//
	int N = qp->dim->N;
	int *nx = qp->dim->nx;
	int *nu = qp->dim->nu;
	int *nb = qp->dim->nb;
	int *ng = qp->dim->ng;
	int *ns = qp->dim->ns;

	REAL mu0 = arg->mu0;

	//
	REAL *ux, *s, *pi, *d_lb, *d_ub, *d_lg, *d_ug, *d_ls, *lam_lb, *lam_ub, *lam_lg, *lam_ug, *lam_ls, *t_lb, *t_ub, *t_lg, *t_ug, *t_ls;
	int *idxb, *idxs;
	int idx;

	REAL thr0 = 1e-1;


	// primal and dual variables
	if(arg->warm_start==2)
		{

		thr0 = 1e-1;

		for(ii=0; ii<=N; ii++)
			{
			lam_lb = qp_sol->lam[ii].pa+0;
			t_lb = qp_sol->t[ii].pa+0;

			for(jj=0; jj<2*nb[ii]+2*ng[ii]+2*ns[ii]; jj++)
				{
				if(lam_lb[jj]<thr0)
					lam_lb[jj] = thr0;
				if(t_lb[jj]<thr0)
					t_lb[jj] = thr0;
				}
			}

		return;
		}


	// ux
	if(arg->warm_start==0)
		{

		// cold start
		for(ii=0; ii<=N; ii++)
			{
			ux = qp_sol->ux[ii].pa;
			for(jj=0; jj<nu[ii]+nx[ii]+2*ns[ii]; jj++)
				{
				ux[jj] = 0.0;
				}
			}

		}
//	else
//		{
//
//		// warm start (keep u and x in solution)
//		for(ii=0; ii<=N; ii++)
//			{
//			ux = qp_sol->ux[ii].pa;
//			for(jj=nu[ii]+nx[ii]; jj<nu[ii]+nx[ii]+2*ns[ii]; jj++)
//				{
//				ux[jj] = 0.0;
//				}
//			}
//
//		}
	
	// pi
	for(ii=0; ii<N; ii++)
		{
		pi = qp_sol->pi[ii].pa;
		for(jj=0; jj<nx[ii+1]; jj++)
			{
			pi[jj] = 0.0;
			}
		}

#if 1 // old version



	// box constraints
	for(ii=0; ii<=N; ii++)
		{
		ux = qp_sol->ux[ii].pa;
		d_lb = qp->d[ii].pa+0;
		d_ub = qp->d[ii].pa+nb[ii]+ng[ii];
		lam_lb = qp_sol->lam[ii].pa+0;
		lam_ub = qp_sol->lam[ii].pa+nb[ii]+ng[ii];
		t_lb = qp_sol->t[ii].pa+0;
		t_ub = qp_sol->t[ii].pa+nb[ii]+ng[ii];
		idxb = qp->idxb[ii];
		for(jj=0; jj<nb[ii]; jj++)
			{
#if 1
			t_lb[jj] = - d_lb[jj] + ux[idxb[jj]];
			t_ub[jj] = - d_ub[jj] - ux[idxb[jj]];
//			printf("\n%d %f %f\n", jj, t_lb[jj], t_ub[jj]);
			if(t_lb[jj]<thr0)
				{
				if(t_ub[jj]<thr0)
					{
//					ux[idxb[jj]] = 0.5*(d_lb[jj] + d_ub[jj]);
					ux[idxb[jj]] = 0.5*(d_lb[jj] - d_ub[jj]);
					t_lb[jj] = thr0;
					t_ub[jj] = thr0;
					}
				else
					{
					t_lb[jj] = thr0;
					ux[idxb[jj]] = d_lb[jj] + thr0;
					}
				}
			else if(t_ub[jj]<thr0)
				{
				t_ub[jj] = thr0;
				ux[idxb[jj]] = - d_ub[jj] - thr0;
				}
#else
			t_lb[jj] = 1.0;
			t_ub[jj] = 1.0;
#endif
			lam_lb[jj] = mu0/t_lb[jj];
			lam_ub[jj] = mu0/t_ub[jj];
			}
//		blasfeo_print_tran_dvec(nb[ii], qp->d+ii, 0);
//		blasfeo_print_tran_dvec(nb[ii], qp->d+ii, nb[ii]+ng[ii]);
//		blasfeo_print_tran_dvec(nu[ii]+nx[ii], qp_sol->ux+ii, 0);
//		blasfeo_print_tran_dvec(nb[ii], qp_sol->t+ii, 0);
//		blasfeo_print_tran_dvec(nb[ii], qp_sol->t+ii, nb[ii]+ng[ii]);
//		exit(1);
		}
	
	// general constraints
	for(ii=0; ii<=N; ii++)
		{
		t_lg = qp_sol->t[ii].pa+nb[ii];
		t_ug = qp_sol->t[ii].pa+2*nb[ii]+ng[ii];
		lam_lg = qp_sol->lam[ii].pa+nb[ii];
		lam_ug = qp_sol->lam[ii].pa+2*nb[ii]+ng[ii];
		d_lg = qp->d[ii].pa+nb[ii];
		d_ug = qp->d[ii].pa+2*nb[ii]+ng[ii];
		ux = qp_sol->ux[ii].pa;
		GEMV_T(nu[ii]+nx[ii], ng[ii], 1.0, qp->DCt+ii, 0, 0, qp_sol->ux+ii, 0, 0.0, qp_sol->t+ii, nb[ii], qp_sol->t+ii, nb[ii]);
		for(jj=0; jj<ng[ii]; jj++)
			{
#if 1
			t_ug[jj] = - t_lg[jj];
			t_lg[jj] -= d_lg[jj];
			t_ug[jj] -= d_ug[jj];
//			t_lg[jj] = fmax(thr0, t_lg[jj]);
//			t_ug[jj] = fmax(thr0, t_ug[jj]);
			t_lg[jj] = thr0>t_lg[jj] ? thr0 : t_lg[jj];
			t_ug[jj] = thr0>t_ug[jj] ? thr0 : t_ug[jj];
#else
			t_lg[jj] = 1.0;
			t_ug[jj] = 1.0;
#endif
			lam_lg[jj] = mu0/t_lg[jj];
			lam_ug[jj] = mu0/t_ug[jj];
			}
		}

	// soft constraints
	for(ii=0; ii<=N; ii++)
		{
		lam_lb = qp_sol->lam[ii].pa+2*nb[ii]+2*ng[ii];
		lam_ub = qp_sol->lam[ii].pa+2*nb[ii]+2*ng[ii]+ns[ii];
		t_lb = qp_sol->t[ii].pa+2*nb[ii]+2*ng[ii];
		t_ub = qp_sol->t[ii].pa+2*nb[ii]+2*ng[ii]+ns[ii];
		for(jj=0; jj<ns[ii]; jj++)
			{
			t_lb[jj] = 1.0; // thr0;
			t_ub[jj] = 1.0; // thr0;
//			t_lb[jj] = sqrt(mu0); // thr0;
//			t_ub[jj] = sqrt(mu0); // thr0;
			lam_lb[jj] = mu0/t_lb[jj];
			lam_ub[jj] = mu0/t_ub[jj];
			}
		}



#else // new version



	for(ii=0; ii<=N; ii++)
		{

//		printf("\nii = %d\n", ii);

		ux = qp_sol->ux[ii].pa;
		s = qp_sol->ux[ii].pa+nu[ii]+nx[ii];
		d_lb = qp->d[ii].pa+0;
		d_ub = qp->d[ii].pa+nb[ii]+ng[ii];
		d_lg = qp->d[ii].pa+nb[ii];
		d_ug = qp->d[ii].pa+2*nb[ii]+ng[ii];
		d_ls = qp->d[ii].pa+2*nb[ii]+2*ng[ii];
		lam_lb = qp_sol->lam[ii].pa+0;
		lam_ub = qp_sol->lam[ii].pa+nb[ii]+ng[ii];
		lam_lg = qp_sol->lam[ii].pa+nb[ii];
		lam_ug = qp_sol->lam[ii].pa+2*nb[ii]+ng[ii];
		lam_ls = qp_sol->lam[ii].pa+2*nb[ii]+2*ng[ii];
		t_lb = qp_sol->t[ii].pa+0;
		t_ub = qp_sol->t[ii].pa+nb[ii]+ng[ii];
		t_lg = qp_sol->t[ii].pa+nb[ii];
		t_ug = qp_sol->t[ii].pa+2*nb[ii]+ng[ii];
		t_ls = qp_sol->t[ii].pa+2*nb[ii]+2*ng[ii];
		idxb = qp->idxb[ii];
		idxs = qp->idxs[ii];

		// lower bound on slacks
		AXPY(2*ns[ii], -1.0, qp->d+ii, 2*nb[ii]+2*ng[ii], qp_sol->ux+ii, nu[ii]+nx[ii], qp_sol->t+ii, 2*nb[ii]+2*ng[ii]);
		for(jj=0; jj<2*ns[ii]; jj++)
			{
#if 1
			if(t_ls[jj]<thr0)
				{
				t_ls[jj] = thr0; //1.0;
				s[jj] = d_ls[jj] + t_ls[jj];
				}
#else
			t_ls[jj] = 1.0;
//			t_ls[jj] = sqrt(mu0);
#endif
			}
//		blasfeo_print_tran_dvec(2*ns[ii], qp_sol->ux+ii, nu[ii]+nx[ii]);
//		blasfeo_print_tran_dvec(2*ns[ii], qp_sol->t+ii, 2*nb[ii]+2*ng[ii]);

		// upper and lower bounds on inputs and states
		VECEX_SP(nb[ii], 1.0, qp->idxb[ii], qp_sol->ux+ii, 0, qp_sol->t+ii, 0);
		VECCPSC(nb[ii], -1.0, qp_sol->t+ii, 0, qp_sol->t+ii, nb[ii]+ng[ii]);
		for(jj=0; jj<ns[ii]; jj++)
			{
			idx = idxs[jj];
			if(idx<nb[ii])
				{
				// softed bound
				t_lb[idx] += s[jj];
				t_ub[idx] += s[ns[ii]+jj];
				}
			}
		AXPY(nb[ii], -1.0, qp->d+ii, 0, qp_sol->t+ii, 0, qp_sol->t+ii, 0);
		AXPY(nb[ii], -1.0, qp->d+ii, nb[ii]+ng[ii], qp_sol->t+ii, nb[ii]+ng[ii], qp_sol->t+ii, nb[ii]+ng[ii]);
//		blasfeo_print_tran_dvec(nb[ii], qp_sol->t+ii, 0);
//		blasfeo_print_tran_dvec(nb[ii], qp_sol->t+ii, nb[ii]+ng[ii]);
		for(jj=0; jj<nb[ii]; jj++)
			{
#if 1
			if(t_lb[jj]<thr0)
				{
				if(t_ub[jj]<thr0)
					{
//					ux[idxb[jj]] = 0.5*(d_lb[jj] + d_ub[jj]);
					ux[idxb[jj]] = 0.5*(d_lb[jj] - d_ub[jj]);
					t_lb[jj] = thr0;
					t_ub[jj] = thr0;
					}
				else
					{
					t_lb[jj] = thr0;
					ux[idxb[jj]] = d_lb[jj] + thr0;
					}
				}
			else if(t_ub[jj]<thr0)
				{
				t_ub[jj] = thr0;
				ux[idxb[jj]] = - d_ub[jj] - thr0;
				}
#else
			t_lb[jj] = 1.0;
			t_ub[jj] = 1.0;
#endif
			}
//		blasfeo_print_tran_dvec(nu[ii]+nx[ii], qp_sol->ux+ii, 0);
//		blasfeo_print_tran_dvec(nb[ii], qp_sol->t+ii, 0);
//		blasfeo_print_tran_dvec(nb[ii], qp_sol->t+ii, nb[ii]+ng[ii]);

		// upper and lower general constaints
		GEMV_T(nu[ii]+nx[ii], ng[ii], 1.0, qp->DCt+ii, 0, 0, qp_sol->ux+ii, 0, 0.0, qp_sol->t+ii, nb[ii], qp_sol->t+ii, nb[ii]);
		VECCPSC(ng[ii], -1.0, qp_sol->t+ii, nb[ii], qp_sol->t+ii, 2*nb[ii]+ng[ii]);
//		blasfeo_print_tran_dvec(ng[ii], qp_sol->t+ii, nb[ii]);
//		blasfeo_print_tran_dvec(ng[ii], qp_sol->t+ii, 2*nb[ii]+ng[ii]);
		for(jj=0; jj<ns[ii]; jj++)
			{
			idx = idxs[jj];
			if(idx>=nb[ii])
				{
				// softed general constraint
				idx -= nb[ii];
				t_lg[idx] += s[jj];
				t_ug[idx] += s[ns[ii]+jj];
				}
			}
//		blasfeo_print_tran_dvec(ng[ii], qp_sol->t+ii, nb[ii]);
//		blasfeo_print_tran_dvec(ng[ii], qp_sol->t+ii, 2*nb[ii]+ng[ii]);
		AXPY(ng[ii], -1.0, qp->d+ii, nb[ii], qp_sol->t+ii, nb[ii], qp_sol->t+ii, nb[ii]);
		AXPY(ng[ii], -1.0, qp->d+ii, 2*nb[ii]+ng[ii], qp_sol->t+ii, 2*nb[ii]+ng[ii], qp_sol->t+ii, 2*nb[ii]+ng[ii]);
		for(jj=0; jj<ng[ii]; jj++)
			{
#if 1
			t_lg[jj] = thr0>t_lg[jj] ? thr0 : t_lg[jj];
			t_ug[jj] = thr0>t_ug[jj] ? thr0 : t_ug[jj];
#else
			t_lg[jj] = 1.0;
			t_ug[jj] = 1.0;
#endif
			}
//		blasfeo_print_tran_dvec(ng[ii], qp_sol->t+ii, nb[ii]);
//		blasfeo_print_tran_dvec(ng[ii], qp_sol->t+ii, 2*nb[ii]+ng[ii]);

		// multipliers
		for(jj=0; jj<2*nb[ii]+2*ng[ii]+2*ns[ii]; jj++)
			lam_lb[jj] = mu0/t_lb[jj];

		}

//	exit(1);



#endif // new version



	return;

	}



void OCP_QP_IPM_ABS_STEP(int kk, struct OCP_QP *qp, struct OCP_QP_SOL *qp_sol, struct OCP_QP_IPM_ARG *arg, struct OCP_QP_IPM_WS *ws)
	{
	
	struct CORE_QP_IPM_WORKSPACE *cws = ws->core_workspace;

	int N = qp->dim->N;
	int *nx = qp->dim->nx;
	int *nu = qp->dim->nu;
	int *nb = qp->dim->nb;
	int *ng = qp->dim->ng;
	int *ns = qp->dim->ns;

	int ii;

	REAL tmp;
	REAL mu_aff0; //, mu;

	VECSC(cws->nc, -1.0, ws->tmp_m, 0);

	BACKUP_RES_M(cws);

	// fact solve
	FACT_SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
//blasfeo_print_tran_dvec(cws->nv, ws->sol_step->ux, 0);

	// compute step
	AXPY(cws->nv, -1.0, qp_sol->ux, 0, ws->sol_step->ux, 0, ws->sol_step->ux, 0);
	AXPY(cws->ne, -1.0, qp_sol->pi, 0, ws->sol_step->pi, 0, ws->sol_step->pi, 0);
	AXPY(cws->nc, -1.0, qp_sol->lam, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
	AXPY(cws->nc, -1.0, qp_sol->t, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
	if(ws->mask_constr)
		{
		// mask out disregarded constraints
		for(ii=0; ii<=N; ii++)
			VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
		VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
		VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
		}

	// alpha
	COMPUTE_ALPHA_QP(cws);
	if(kk+1<ws->stat_max)
		ws->stat[ws->stat_m*(kk+1)+0] = cws->alpha;

	// Mehrotra's predictor-corrector
	if(arg->pred_corr==1)
		{
		// mu_aff
		COMPUTE_MU_AFF_QP(cws);
		if(kk+1<ws->stat_max)
			ws->stat[ws->stat_m*(kk+1)+1] = cws->mu_aff;

		tmp = cws->mu_aff/cws->mu;
		cws->sigma = tmp*tmp*tmp;
		if(kk+1<ws->stat_max)
			ws->stat[ws->stat_m*(kk+1)+2] = cws->sigma;

		COMPUTE_CENTERING_CORRECTION_QP(cws);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_m, 0, ws->res->res_m, 0);
			}

		// fact and solve kkt
		ws->use_Pb = 1;
		SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);

		// compute step
		AXPY(cws->nv, -1.0, qp_sol->ux, 0, ws->sol_step->ux, 0, ws->sol_step->ux, 0);
		AXPY(cws->ne, -1.0, qp_sol->pi, 0, ws->sol_step->pi, 0, ws->sol_step->pi, 0);
		AXPY(cws->nc, -1.0, qp_sol->lam, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
		AXPY(cws->nc, -1.0, qp_sol->t, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
			}

		// alpha
		COMPUTE_ALPHA_QP(cws);
		if(kk+1<ws->stat_max)
			ws->stat[ws->stat_m*(kk+1)+3] = cws->alpha;

		// conditional Mehrotra's predictor-corrector
		if(arg->cond_pred_corr==1)
			{

			// save mu_aff (from prediction sol_step)
			mu_aff0 = cws->mu_aff;

			// compute mu for predictor-corrector-centering
			COMPUTE_MU_AFF_QP(cws);

//			if(cws->mu_aff > 2.0*cws->mu)
			if(cws->mu_aff > 2.0*mu_aff0)
				{

				// centering direction
				COMPUTE_CENTERING_QP(cws);
				if(ws->mask_constr)
					{
					// mask out disregarded constraints
					VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_m, 0, ws->res->res_m, 0);
					}

				// solve kkt
				SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
				// compute step
				AXPY(cws->nv, -1.0, qp_sol->ux, 0, ws->sol_step->ux, 0, ws->sol_step->ux, 0);
				AXPY(cws->ne, -1.0, qp_sol->pi, 0, ws->sol_step->pi, 0, ws->sol_step->pi, 0);
				AXPY(cws->nc, -1.0, qp_sol->lam, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
				AXPY(cws->nc, -1.0, qp_sol->t, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
				if(ws->mask_constr)
					{
					// mask out disregarded constraints
					for(ii=0; ii<=N; ii++)
						VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
					VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
					VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
					}

				// alpha
				COMPUTE_ALPHA_QP(cws);
				if(kk+1<ws->stat_max)
					ws->stat[ws->stat_m*(kk+1)+3] = cws->alpha;

				}
			}

		}

	//
	UPDATE_VAR_QP(cws);
	if(ws->mask_constr)
		{
		// mask out disregarded constraints
		VECMUL(cws->nc, qp->d_mask, 0, qp_sol->lam, 0, qp_sol->lam, 0);
		}

	return;

	}



void OCP_QP_IPM_DELTA_STEP(int kk, struct OCP_QP *qp, struct OCP_QP_SOL *qp_sol, struct OCP_QP_IPM_ARG *arg, struct OCP_QP_IPM_WS *ws)
	{

//d_ocp_qp_print(qp->dim, qp);
//d_ocp_qp_sol_print(qp->dim, qp_sol);
//exit(1);
	// dim
	int N = qp->dim->N;
	int *nx = qp->dim->nx;
	int *nu = qp->dim->nu;
	int *nb = qp->dim->nb;
	int *ng = qp->dim->ng;
	int *ns = qp->dim->ns;

	struct CORE_QP_IPM_WORKSPACE *cws = ws->core_workspace;

	int itref0=0, itref1=0, iter_ref_step;
	int ii;
	REAL tmp;
	REAL mu_aff0, mu;

	REAL itref_qp_norm[4] = {0,0,0,0};
	REAL itref_qp_norm0[4] = {0,0,0,0};

	int force_lq = 0;

	// step body

	BACKUP_RES_M(cws);

	// fact and solve kkt
	if(ws->lq_fact==0)
		{

		// syrk+cholesky
		FACT_SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
			}

		}
	else if(ws->lq_fact==1 & force_lq==0)
		{

		// syrk+chol, switch to lq when needed
		FACT_SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
			}

		// compute res of linear system
		OCP_QP_RES_COMPUTE_LIN(ws->qp_step, qp_sol, ws->sol_step, ws->res_itref, ws->res_workspace);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->res_itref->res_g+ii, nu[ii]+nx[ii], ws->res_itref->res_g+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->res_itref->res_d, 0, ws->res_itref->res_d, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->res_itref->res_m, 0, ws->res_itref->res_m, 0);
			}
		OCP_QP_RES_COMPUTE_INF_NORM(ws->res_itref);
		itref_qp_norm[0] = ws->res_itref->res_max[0];
		itref_qp_norm[1] = ws->res_itref->res_max[1];
		itref_qp_norm[2] = ws->res_itref->res_max[2];
		itref_qp_norm[3] = ws->res_itref->res_max[3];

		// inaccurate factorization: switch to lq
		if(
#ifdef USE_C99_MATH
			( itref_qp_norm[0]==0.0 & isnan(BLASFEO_DVECEL(ws->res_itref->res_g+0, 0)) ) |
#else
			( itref_qp_norm[0]==0.0 & BLASFEO_DVECEL(ws->res_itref->res_g+0, 0)!=BLASFEO_DVECEL(ws->res_itref->res_g+0, 0) ) |
#endif
			itref_qp_norm[0]>1e-5 |
			itref_qp_norm[1]>1e-5 |
			itref_qp_norm[2]>1e-5 |
			itref_qp_norm[3]>1e-5 )
			{

			// refactorize using lq
			FACT_LQ_SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
			if(ws->mask_constr)
				{
				// mask out disregarded constraints
				for(ii=0; ii<=N; ii++)
					VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
				VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
				VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
				}

			// switch to lq
			force_lq = 1;

			}

		}
	else // ws->lq_fact==2
		{

		FACT_LQ_SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
			}

		}

	// iterative refinement on prediction step
	for(itref0=0; itref0<arg->itref_pred_max; itref0++)
		{

		OCP_QP_RES_COMPUTE_LIN(ws->qp_step, qp_sol, ws->sol_step, ws->res_itref, ws->res_workspace);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->res_itref->res_g+ii, nu[ii]+nx[ii], ws->res_itref->res_g+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->res_itref->res_d, 0, ws->res_itref->res_d, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->res_itref->res_m, 0, ws->res_itref->res_m, 0);
			}
		OCP_QP_RES_COMPUTE_INF_NORM(ws->res_itref);
		itref_qp_norm[0] = ws->res_itref->res_max[0];
		itref_qp_norm[1] = ws->res_itref->res_max[1];
		itref_qp_norm[2] = ws->res_itref->res_max[2];
		itref_qp_norm[3] = ws->res_itref->res_max[3];

		if(itref0==0)
			{
			itref_qp_norm0[0] = itref_qp_norm[0];
			itref_qp_norm0[1] = itref_qp_norm[1];
			itref_qp_norm0[2] = itref_qp_norm[2];
			itref_qp_norm0[3] = itref_qp_norm[3];
			}

		if( \
				(itref_qp_norm[0]<1e0*arg->res_g_max | itref_qp_norm[0]<1e-3*ws->res->res_max[0]) & \
				(itref_qp_norm[1]<1e0*arg->res_b_max | itref_qp_norm[1]<1e-3*ws->res->res_max[1]) & \
				(itref_qp_norm[2]<1e0*arg->res_d_max | itref_qp_norm[2]<1e-3*ws->res->res_max[2]) & \
				(itref_qp_norm[3]<1e0*arg->res_m_max | itref_qp_norm[3]<1e-3*ws->res->res_max[3]) )
			{
			break;
			}

		ws->use_Pb = 0;
		SOLVE_KKT_STEP_OCP_QP(ws->qp_itref, ws->sol_itref, arg, ws);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
			}

		for(ii=0; ii<=N; ii++)
			AXPY(nu[ii]+nx[ii]+2*ns[ii], 1.0, ws->sol_itref->ux+ii, 0, ws->sol_step->ux+ii, 0, ws->sol_step->ux+ii, 0);
		for(ii=0; ii<N; ii++)
			AXPY(nx[ii+1], 1.0, ws->sol_itref->pi+ii, 0, ws->sol_step->pi+ii, 0, ws->sol_step->pi+ii, 0);
		for(ii=0; ii<=N; ii++)
			AXPY(2*nb[ii]+2*ng[ii]+2*ns[ii], 1.0, ws->sol_itref->lam+ii, 0, ws->sol_step->lam+ii, 0, ws->sol_step->lam+ii, 0);
		for(ii=0; ii<=N; ii++)
			AXPY(2*nb[ii]+2*ng[ii]+2*ns[ii], 1.0, ws->sol_itref->t+ii, 0, ws->sol_step->t+ii, 0, ws->sol_step->t+ii, 0);

		}
	if(kk+1<ws->stat_max)
		ws->stat[ws->stat_m*(kk+1)+9] = itref0;

	// alpha
	COMPUTE_ALPHA_QP(cws);
	if(kk+1<ws->stat_max)
		ws->stat[ws->stat_m*(kk+1)+0] = cws->alpha;

	// Mehrotra's predictor-corrector
	if(arg->pred_corr==1)
		{
		// mu_aff
		COMPUTE_MU_AFF_QP(cws);
		if(kk+1<ws->stat_max)
			ws->stat[ws->stat_m*(kk+1)+1] = cws->mu_aff;

		tmp = cws->mu_aff/cws->mu;
		cws->sigma = tmp*tmp*tmp;
		if(kk+1<ws->stat_max)
			ws->stat[ws->stat_m*(kk+1)+2] = cws->sigma;

		COMPUTE_CENTERING_CORRECTION_QP(cws);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_m, 0, ws->res->res_m, 0);
			}

		// fact and solve kkt
		ws->use_Pb = 1;
		SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
			}

		// alpha
		COMPUTE_ALPHA_QP(cws);
		if(kk+1<ws->stat_max)
			ws->stat[ws->stat_m*(kk+1)+3] = cws->alpha;

		// conditional Mehrotra's predictor-corrector
		if(arg->cond_pred_corr==1)
			{

			// save mu_aff (from prediction step)
			mu_aff0 = cws->mu_aff;

			// compute mu for predictor-corrector-centering
			COMPUTE_MU_AFF_QP(cws);

//				if(cws->mu_aff > 2.0*cws->mu)
			if(cws->mu_aff > 2.0*mu_aff0)
				{

				// centering direction
				COMPUTE_CENTERING_QP(cws);
				if(ws->mask_constr)
					{
					// mask out disregarded constraints
					VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_m, 0, ws->res->res_m, 0);
					}

				// solve kkt
				ws->use_Pb = 1;
				SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
				if(ws->mask_constr)
					{
					// mask out disregarded constraints
					for(ii=0; ii<=N; ii++)
						VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
					VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
					VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
					}

				// alpha
				COMPUTE_ALPHA_QP(cws);
				if(kk+1<ws->stat_max)
					ws->stat[ws->stat_m*(kk+1)+3] = cws->alpha;

				}

			}

		iter_ref_step = 0;
		for(itref1=0; itref1<arg->itref_corr_max; itref1++)
			{

			OCP_QP_RES_COMPUTE_LIN(ws->qp_step, qp_sol, ws->sol_step, ws->res_itref, ws->res_workspace);
			if(ws->mask_constr)
				{
				// mask out disregarded constraints
				for(ii=0; ii<=N; ii++)
					VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->res_itref->res_g+ii, nu[ii]+nx[ii], ws->res_itref->res_g+ii, nu[ii]+nx[ii]);
				VECMUL(cws->nc, qp->d_mask, 0, ws->res_itref->res_d, 0, ws->res_itref->res_d, 0);
				VECMUL(cws->nc, qp->d_mask, 0, ws->res_itref->res_m, 0, ws->res_itref->res_m, 0);
				}
			OCP_QP_RES_COMPUTE_INF_NORM(ws->res_itref);
			itref_qp_norm[0] = ws->res_itref->res_max[0];
			itref_qp_norm[1] = ws->res_itref->res_max[1];
			itref_qp_norm[2] = ws->res_itref->res_max[2];
			itref_qp_norm[3] = ws->res_itref->res_max[3];

			if(itref1==0)
				{
				itref_qp_norm0[0] = itref_qp_norm[0];
				itref_qp_norm0[1] = itref_qp_norm[1];
				itref_qp_norm0[2] = itref_qp_norm[2];
				itref_qp_norm0[3] = itref_qp_norm[3];
				}

			if( \
					(itref_qp_norm[0]<1e0*arg->res_g_max | itref_qp_norm[0]<1e-3*ws->res->res_max[0]) & \
					(itref_qp_norm[1]<1e0*arg->res_b_max | itref_qp_norm[1]<1e-3*ws->res->res_max[1]) & \
					(itref_qp_norm[2]<1e0*arg->res_d_max | itref_qp_norm[2]<1e-3*ws->res->res_max[2]) & \
					(itref_qp_norm[3]<1e0*arg->res_m_max | itref_qp_norm[3]<1e-3*ws->res->res_max[3]) )
				{
				break;
				}

			ws->use_Pb = 0;
			SOLVE_KKT_STEP_OCP_QP(ws->qp_itref, ws->sol_itref, arg, ws);
			if(ws->mask_constr)
				{
				// mask out disregarded constraints
				for(ii=0; ii<=N; ii++)
					VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii], ws->sol_step->ux+ii, nu[ii]+nx[ii]);
				VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->t, 0, ws->sol_step->t, 0);
				VECMUL(cws->nc, qp->d_mask, 0, ws->sol_step->lam, 0, ws->sol_step->lam, 0);
				}
			iter_ref_step = 1;

			for(ii=0; ii<=N; ii++)
				AXPY(nu[ii]+nx[ii]+2*ns[ii], 1.0, ws->sol_itref->ux+ii, 0, ws->sol_step->ux+ii, 0, ws->sol_step->ux+ii, 0);
			for(ii=0; ii<N; ii++)
				AXPY(nx[ii+1], 1.0, ws->sol_itref->pi+ii, 0, ws->sol_step->pi+ii, 0, ws->sol_step->pi+ii, 0);
			for(ii=0; ii<=N; ii++)
				AXPY(2*nb[ii]+2*ng[ii]+2*ns[ii], 1.0, ws->sol_itref->lam+ii, 0, ws->sol_step->lam+ii, 0, ws->sol_step->lam+ii, 0);
			for(ii=0; ii<=N; ii++)
				AXPY(2*nb[ii]+2*ng[ii]+2*ns[ii], 1.0, ws->sol_itref->t+ii, 0, ws->sol_step->t+ii, 0, ws->sol_step->t+ii, 0);

			}

		if(iter_ref_step)
			{
			// alpha
			COMPUTE_ALPHA_QP(cws);
			if(kk+1<ws->stat_max)
				ws->stat[ws->stat_m*(kk+1)+3] = cws->alpha;
			}

		}
	if(kk+1<ws->stat_max)
		ws->stat[ws->stat_m*(kk+1)+10] = itref1;

	//
	UPDATE_VAR_QP(cws);
	if(ws->mask_constr)
		{
		// mask out disregarded constraints
		VECMUL(cws->nc, qp->d_mask, 0, qp_sol->lam, 0, qp_sol->lam, 0);
		}

	return;

	}



void OCP_QP_IPM_SOLVE(struct OCP_QP *qp, struct OCP_QP_SOL *qp_sol, struct OCP_QP_IPM_ARG *arg, struct OCP_QP_IPM_WS *ws)
	{

#if 0
	OCP_QP_DIM_PRINT(qp->dim);
	OCP_QP_PRINT(qp->dim, qp);
#endif

	// dim
	int N = qp->dim->N;
	int *nx = qp->dim->nx;
	int *nu = qp->dim->nu;
	int *nb = qp->dim->nb;
	int *ng = qp->dim->ng;
	int *ns = qp->dim->ns;

	struct CORE_QP_IPM_WORKSPACE *cws = ws->core_workspace;

	int kk, ii;
	REAL mu;

	// arg to core workspace
	cws->lam_min = arg->lam_min;
	cws->t_min = arg->t_min;

	// alias qp vectors into qp_sol
	cws->v = qp_sol->ux->pa;
	cws->pi = qp_sol->pi->pa;
	cws->lam = qp_sol->lam->pa;
	cws->t = qp_sol->t->pa;

	// alias members of qp_step
	ws->qp_step->dim = qp->dim;
	ws->qp_step->RSQrq = qp->RSQrq;
	ws->qp_step->BAbt = qp->BAbt;
	ws->qp_step->DCt = qp->DCt;
	ws->qp_step->Z = qp->Z;
	ws->qp_step->idxb = qp->idxb;
	ws->qp_step->idxs = qp->idxs;
	ws->qp_step->rqz = ws->res->res_g;
	ws->qp_step->b = ws->res->res_b;
	ws->qp_step->d = ws->res->res_d;
	ws->qp_step->m = ws->res->res_m;

	// alias members of qp_itref
	ws->qp_itref->dim = qp->dim;
	ws->qp_itref->RSQrq = qp->RSQrq;
	ws->qp_itref->BAbt = qp->BAbt;
	ws->qp_itref->DCt = qp->DCt;
	ws->qp_itref->Z = qp->Z;
	ws->qp_itref->idxb = qp->idxb;
	ws->qp_itref->idxs = qp->idxs;
	ws->qp_itref->rqz = ws->res_itref->res_g;
	ws->qp_itref->b = ws->res_itref->res_b;
	ws->qp_itref->d = ws->res_itref->res_d;
	ws->qp_itref->m = ws->res_itref->res_m;

	REAL *qp_res_max = ws->res->res_max;
	qp_res_max[0] = 0;
	qp_res_max[1] = 0;
	qp_res_max[2] = 0;
	qp_res_max[3] = 0;


	// detect constr mask
	int mask_unconstr;
	int nc_mask = 0;
	for(ii=0; ii<cws->nc; ii++)
		{
		if(qp->d_mask->pa[ii]!=0.0)
			nc_mask++;
		}
	if(nc_mask<cws->nc)
		{
		ws->mask_constr = 1;
		}
	else
		{
		ws->mask_constr = 0;
		}
	if(nc_mask==0)
		{
		mask_unconstr = 1;
		cws->nc_mask = 0;
		cws->nc_mask_inv = 0.0;
		}
	else
		{
		mask_unconstr = 0;
		cws->nc_mask = nc_mask;
		cws->nc_mask_inv = 1.0/nc_mask;
		}


	// no constraints
	if(cws->nc==0 | mask_unconstr==1)
		{
		FACT_SOLVE_KKT_UNCONSTR_OCP_QP(qp, qp_sol, arg, ws);
		if(arg->comp_res_exit)
			{
			OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);
			// XXX no constraints, so no mask
			OCP_QP_RES_COMPUTE_INF_NORM(ws->res);
			if(0<ws->stat_max)
				{
				ws->stat[5] = qp_res_max[0];
				ws->stat[6] = qp_res_max[1];
				ws->stat[7] = qp_res_max[2];
				ws->stat[8] = qp_res_max[3];
				}
			cws->mu = ws->res->res_mu;
			}
		ws->iter = 0;
		ws->status = 0;
		return;
		}


	// init solver
	OCP_QP_INIT_VAR(qp, qp_sol, arg, ws);
	if(ws->mask_constr)
		{
		// mask out disregarded constraints
		VECMUL(cws->nc, qp->d_mask, 0, qp_sol->lam, 0, qp_sol->lam, 0);
		}

	cws->alpha = 1.0;



	// absolute IPM formulation

	if(arg->abs_form)
		{

		// alias members of qp_step
		ws->qp_step->dim = qp->dim;
		ws->qp_step->RSQrq = qp->RSQrq;
		ws->qp_step->BAbt = qp->BAbt;
		ws->qp_step->DCt = qp->DCt;
		ws->qp_step->Z = qp->Z;
		ws->qp_step->idxb = qp->idxb;
		ws->qp_step->idxs = qp->idxs;
		ws->qp_step->rqz = qp->rqz;
		ws->qp_step->b = qp->b;
		ws->qp_step->d = qp->d;
		ws->qp_step->m = ws->tmp_m;

		// alias core workspace
		cws->res_m = ws->qp_step->m->pa;
		cws->res_m_bkp = ws->qp_step->m->pa; // TODO remove (as in dense qp) ???

		mu = VECMULDOT(cws->nc, qp_sol->lam, 0, qp_sol->t, 0, ws->tmp_m, 0);
		mu /= cws->nc;
		cws->mu = mu;

		// IPM loop (absolute formulation)
		for(kk=0; \
				kk<arg->iter_max & \
				cws->alpha>arg->alpha_min & \
				mu>arg->res_m_max; kk++)
			{

			// compute delta step
			OCP_QP_IPM_ABS_STEP(kk, qp, qp_sol, arg, ws);

			// compute mu
			mu = VECMULDOT(cws->nc, qp_sol->lam, 0, qp_sol->t, 0, ws->tmp_m, 0);
			mu /= cws->nc;
			cws->mu = mu;
			if(kk+1<ws->stat_max)
				ws->stat[ws->stat_m*(kk+1)+4] = mu;

			}

		if(arg->comp_res_exit & arg->comp_dual_sol)
			{
			// compute residuals
			OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);
			if(ws->mask_constr)
				{
				// mask out disregarded constraints
				for(ii=0; ii<=N; ii++)
					VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->res->res_g+ii, nu[ii]+nx[ii], ws->res->res_g+ii, nu[ii]+nx[ii]);
				VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_d, 0, ws->res->res_d, 0);
				VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_m, 0, ws->res->res_m, 0);
				}
			OCP_QP_RES_COMPUTE_INF_NORM(ws->res);
			// save infinity norm of residuals
			// XXX it is already kk+1
			if(kk<ws->stat_max)
				{
				ws->stat[ws->stat_m*(kk+0)+5] = qp_res_max[0];
				ws->stat[ws->stat_m*(kk+0)+6] = qp_res_max[1];
				ws->stat[ws->stat_m*(kk+0)+7] = qp_res_max[2];
				ws->stat[ws->stat_m*(kk+0)+8] = qp_res_max[3];
				}
			}

		ws->iter = kk;

		if(kk == arg->iter_max)
			{
			// max iteration number reached
			ws->status = 1;
			}
		else if(cws->alpha <= arg->alpha_min)
			{
			// min step lenght
			ws->status = 2;
			}
#ifdef USE_C99_MATH
		else if(isnan(cws->mu))
			{
			// NaN in the solution
			ws->status = 3;
			}
#else
		else if(cws->mu != cws->mu)
			{
			// NaN in the solution
			ws->status = 3;
			}
#endif
		else
			{
			// normal return
			ws->status = 0;
			}

		return;

		}



	// compute residuals
	OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);
	if(ws->mask_constr)
		{
		// mask out disregarded constraints
		for(ii=0; ii<=N; ii++)
			VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->res->res_g+ii, nu[ii]+nx[ii], ws->res->res_g+ii, nu[ii]+nx[ii]);
		VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_d, 0, ws->res->res_d, 0);
		VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_m, 0, ws->res->res_m, 0);
		}
	cws->mu = ws->res->res_mu;
	OCP_QP_RES_COMPUTE_INF_NORM(ws->res);
	// save infinity norm of residuals
	if(0<ws->stat_max)
		{
		ws->stat[ws->stat_m*(0)+5] = qp_res_max[0];
		ws->stat[ws->stat_m*(0)+6] = qp_res_max[1];
		ws->stat[ws->stat_m*(0)+7] = qp_res_max[2];
		ws->stat[ws->stat_m*(0)+8] = qp_res_max[3];
		}




	// relative (delta) IPM formulation

	// IPM loop
	for(kk=0; kk<arg->iter_max & \
			cws->alpha>arg->alpha_min & \
			(qp_res_max[0]>arg->res_g_max | \
			qp_res_max[1]>arg->res_b_max | \
			qp_res_max[2]>arg->res_d_max | \
			qp_res_max[3]>arg->res_m_max); kk++)
		{

		// compute delta step
		OCP_QP_IPM_DELTA_STEP(kk, qp, qp_sol, arg, ws);

		// compute residuals
		OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);
		if(ws->mask_constr)
			{
			// mask out disregarded constraints
			for(ii=0; ii<=N; ii++)
				VECMUL(2*ns[ii], qp->d_mask+ii, 2*nb[ii]+2*ng[ii], ws->res->res_g+ii, nu[ii]+nx[ii], ws->res->res_g+ii, nu[ii]+nx[ii]);
			VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_d, 0, ws->res->res_d, 0);
			VECMUL(cws->nc, qp->d_mask, 0, ws->res->res_m, 0, ws->res->res_m, 0);
			}
		cws->mu = ws->res->res_mu;
		if(kk+1<ws->stat_max)
			ws->stat[ws->stat_m*(kk+1)+4] = ws->res->res_mu;
		OCP_QP_RES_COMPUTE_INF_NORM(ws->res);
		// save infinity norm of residuals
		if(kk+1<ws->stat_max)
			{
			ws->stat[ws->stat_m*(kk+1)+5] = qp_res_max[0];
			ws->stat[ws->stat_m*(kk+1)+6] = qp_res_max[1];
			ws->stat[ws->stat_m*(kk+1)+7] = qp_res_max[2];
			ws->stat[ws->stat_m*(kk+1)+8] = qp_res_max[3];
			}

		}

	ws->iter = kk;

	if(kk == arg->iter_max)
		{
		// max iteration number reached
		ws->status = 1;
		}
	else if(cws->alpha <= arg->alpha_min)
		{
		// min step lenght
		ws->status = 2;
		}
#ifdef USE_C99_MATH
	else if(isnan(cws->mu))
		{
		// NaN in the solution
		ws->status = 3;
		}
#else
	else if(cws->mu != cws->mu)
		{
		// NaN in the solution
		ws->status = 3;
		}
#endif
	else
		{
		// normal return
		ws->status = 0;
		}

	return;

	}



void OCP_QP_IPM_PREDICT(struct OCP_QP *qp, struct OCP_QP_SOL *qp_sol, struct OCP_QP_IPM_ARG *arg, struct OCP_QP_IPM_WS *ws)
	{

#if 0
	OCP_QP_DIM_PRINT(qp->dim);
	OCP_QP_PRINT(qp->dim, qp);
#endif

	int ii;

	struct CORE_QP_IPM_WORKSPACE *cws = ws->core_workspace;

	// arg to core workspace
	cws->lam_min = arg->lam_min;
	cws->t_min = arg->t_min;

	// alias qp vectors into qp_sol
	cws->v = qp_sol->ux->pa;
	cws->pi = qp_sol->pi->pa;
	cws->lam = qp_sol->lam->pa;
	cws->t = qp_sol->t->pa;

	// alias members of qp_step
	ws->qp_step->dim = qp->dim;
	ws->qp_step->RSQrq = qp->RSQrq;
	ws->qp_step->BAbt = qp->BAbt;
	ws->qp_step->DCt = qp->DCt;
	ws->qp_step->Z = qp->Z;
	ws->qp_step->idxb = qp->idxb;
	ws->qp_step->idxs = qp->idxs;
	ws->qp_step->rqz = ws->res->res_g;
	ws->qp_step->b = ws->res->res_b;
	ws->qp_step->d = ws->res->res_d;
	ws->qp_step->m = ws->res->res_m;

	// TODO ?

	// blasfeo alias for residuals
	struct STRVEC str_res_g;
	struct STRVEC str_res_b;
	struct STRVEC str_res_d;
	struct STRVEC str_res_m;
	str_res_g.m = cws->nv;
	str_res_b.m = cws->ne;
	str_res_d.m = cws->nc;
	str_res_m.m = cws->nc;
	str_res_g.pa = cws->res_g;
	str_res_b.pa = cws->res_b;
	str_res_d.pa = cws->res_d;
	str_res_m.pa = cws->res_m;

	REAL *qp_res_max = ws->res->res_max;
	qp_res_max[0] = 0;
	qp_res_max[1] = 0;
	qp_res_max[2] = 0;
	qp_res_max[3] = 0;

	// load sol from bkp
	for(ii=0; ii<cws->nv; ii++)
		cws->v[ii] = cws->v_bkp[ii];
	for(ii=0; ii<cws->ne; ii++)
		cws->pi[ii] = cws->pi_bkp[ii];
	for(ii=0; ii<cws->nc; ii++)
		cws->lam[ii] = cws->lam_bkp[ii];
	for(ii=0; ii<cws->nc; ii++)
		cws->t[ii] = cws->t_bkp[ii];

	// TODO absolute formulation !!!!!

	// TODO robust formulation !!!!!

	// compute residuals
	OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);

	// compute infinity norm of residuals
	VECNRM_INF(cws->nv, &str_res_g, 0, &qp_res_max[0]);
	VECNRM_INF(cws->ne, &str_res_b, 0, &qp_res_max[1]);
	VECNRM_INF(cws->nc, &str_res_d, 0, &qp_res_max[2]);
	VECNRM_INF(cws->nc, &str_res_m, 0, &qp_res_max[3]);

//printf("\npredict\t%e\t%e\t%e\t%e\n", qp_res_max[0], qp_res_max[1], qp_res_max[2], qp_res_max[3]);

	// solve kkt
	ws->use_Pb = 0;
	SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);

	// alpha TODO fix alpha=1 !!!!!
//	COMPUTE_ALPHA_QP(cws);
	cws->alpha = 1.0;

	//
	UPDATE_VAR_QP(cws);

	if(arg->comp_res_pred)
		{
		// compute residuals in exit
		OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);

		// compute infinity norm of residuals
		VECNRM_INF(cws->nv, &str_res_g, 0, &qp_res_max[0]);
		VECNRM_INF(cws->ne, &str_res_b, 0, &qp_res_max[1]);
		VECNRM_INF(cws->nc, &str_res_d, 0, &qp_res_max[2]);
		VECNRM_INF(cws->nc, &str_res_m, 0, &qp_res_max[3]);
		}

//printf("\npredict\t%e\t%e\t%e\t%e\n", qp_res_max[0], qp_res_max[1], qp_res_max[2], qp_res_max[3]);

	// TODO

	// do not change status

	return;

	}



void OCP_QP_IPM_SENS(struct OCP_QP *qp, struct OCP_QP_SOL *qp_sol, struct OCP_QP_IPM_ARG *arg, struct OCP_QP_IPM_WS *ws)
	{

#if 0
	OCP_QP_DIM_PRINT(qp->dim);
	OCP_QP_PRINT(qp->dim, qp);
#endif

	int ii;

	struct CORE_QP_IPM_WORKSPACE *cws = ws->core_workspace;

	// arg to core workspace
	cws->lam_min = arg->lam_min;
	cws->t_min = arg->t_min;

	// alias qp vectors into qp_sol
	cws->v = qp_sol->ux->pa;
	cws->pi = qp_sol->pi->pa;
	cws->lam = qp_sol->lam->pa;
	cws->t = qp_sol->t->pa;

#if 0
	// alias members of qp_step
	ws->qp_step->dim = qp->dim;
	ws->qp_step->RSQrq = qp->RSQrq;
	ws->qp_step->BAbt = qp->BAbt;
	ws->qp_step->DCt = qp->DCt;
	ws->qp_step->Z = qp->Z;
	ws->qp_step->idxb = qp->idxb;
	ws->qp_step->idxs = qp->idxs;
	ws->qp_step->rqz = res->res_g;
	ws->qp_step->b = res->res_b;
	ws->qp_step->d = res->res_d;
	ws->qp_step->m = res->res_m;
#endif

	// TODO ?

#if 0
	// blasfeo alias for residuals
	struct STRVEC str_res_g;
	struct STRVEC str_res_b;
	struct STRVEC str_res_d;
	struct STRVEC str_res_m;
	str_res_g.m = cws->nv;
	str_res_b.m = cws->ne;
	str_res_d.m = cws->nc;
	str_res_m.m = cws->nc;
	str_res_g.pa = cws->res_g;
	str_res_b.pa = cws->res_b;
	str_res_d.pa = cws->res_d;
	str_res_m.pa = cws->res_m;

	REAL *qp_res_max = ws->qp_res_max;
	qp_res_max[0] = 0;
	qp_res_max[1] = 0;
	qp_res_max[2] = 0;
	qp_res_max[3] = 0;
#endif

#if 0
// compute residuals
OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);

// compute infinity norm of residuals
VECNRM_INF(cws->nv, &str_res_g, 0, &qp_res_max[0]);
VECNRM_INF(cws->ne, &str_res_b, 0, &qp_res_max[1]);
VECNRM_INF(cws->nc, &str_res_d, 0, &qp_res_max[2]);
VECNRM_INF(cws->nc, &str_res_m, 0, &qp_res_max[3]);

printf("\npredict\t%e\t%e\t%e\t%e\n", qp_res_max[0], qp_res_max[1], qp_res_max[2], qp_res_max[3]);
#endif

	// load sol from bkp
	for(ii=0; ii<cws->nv; ii++)
		cws->v[ii] = cws->v_bkp[ii];
	for(ii=0; ii<cws->ne; ii++)
		cws->pi[ii] = cws->pi_bkp[ii];
	for(ii=0; ii<cws->nc; ii++)
		cws->lam[ii] = cws->lam_bkp[ii];
	for(ii=0; ii<cws->nc; ii++)
		cws->t[ii] = cws->t_bkp[ii];

//printf("\npredict\t%e\t%e\t%e\t%e\n", qp_res_max[0], qp_res_max[1], qp_res_max[2], qp_res_max[3]);

	// solve kkt
	ws->use_Pb = 0;
//	SOLVE_KKT_STEP_OCP_QP(ws->qp_step, ws->sol_step, arg, ws);
	SOLVE_KKT_STEP_OCP_QP(qp, qp_sol, arg, ws);

#if 0
	// alpha TODO fix alpha=1 !!!!!
//	COMPUTE_ALPHA_QP(cws);
	cws->alpha = 1.0;

	//
	UPDATE_VAR_QP(cws);

	if(arg->comp_res_pred)
		{
		// compute residuals in exit
		OCP_QP_RES_COMPUTE(qp, qp_sol, ws->res, ws->res_workspace);

		// compute infinity norm of residuals
		VECNRM_INF(cws->nv, &str_res_g, 0, &qp_res_max[0]);
		VECNRM_INF(cws->ne, &str_res_b, 0, &qp_res_max[1]);
		VECNRM_INF(cws->nc, &str_res_d, 0, &qp_res_max[2]);
		VECNRM_INF(cws->nc, &str_res_m, 0, &qp_res_max[3]);
		}
#endif

//printf("\npredict\t%e\t%e\t%e\t%e\n", qp_res_max[0], qp_res_max[1], qp_res_max[2], qp_res_max[3]);

	// TODO

	// do not change status

	return;

	}
