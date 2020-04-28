/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2018-2019 Sultan Alsawaf <sultan@kerneltoast.com>.
 */
#ifndef _CPU_INPUT_BOOST_H_
#define _CPU_INPUT_BOOST_H_

#ifdef CONFIG_CPU_INPUT_BOOST
struct boost_drv {
	struct workqueue_struct *wq_i;
	struct workqueue_struct *wq_f;
	struct workqueue_struct *wq_cl1;
	struct workqueue_struct *wq_cl2;
	struct workqueue_struct *wq_istu;
	struct workqueue_struct *wq_mstu;
	struct workqueue_struct *wq_ufs;
	struct workqueue_struct *wq_fstu;
	struct workqueue_struct *wq_gpu;
	struct workqueue_struct *wq_gpu_flex;
	struct workqueue_struct *wq_core;
	struct delayed_work input_unboost;
	struct delayed_work flex_unboost;
	struct delayed_work gpu_flex_unboost;
	struct delayed_work core_unboost;
	struct delayed_work ufs_unboost;
	struct delayed_work cluster1_unboost;
	struct delayed_work cluster2_unboost;
	struct delayed_work input_stune_unboost;
	struct delayed_work max_stune_unboost;
	struct delayed_work flex_stune_unboost;
	struct delayed_work gpu_unboost;
	struct notifier_block cpu_notif;
#ifdef CONFIG_DRM_MSM
	struct notifier_block msm_drm_notif;
#else
	struct notifier_block fb_notif;
#endif
	struct kgsl_device *gpu_device;
	struct kgsl_pwrctrl *gpu_pwr;
	wait_queue_head_t cpu_boost_waitq;
	wait_queue_head_t gpu_boost_waitq;
	wait_queue_head_t stune_boost_waitq;
	unsigned long cpu_state;
	unsigned long stune_state;
	unsigned long gpu_state;
	unsigned int cpu;
};

extern struct boost_drv *gov_cpu_state;
extern bool boost_gold;
extern unsigned int base_stune_boost;
extern unsigned int default_level_stune_boost;
extern unsigned int sleep_freq_lp;
extern unsigned int sleep_freq_hp;
extern unsigned int sleep_freq_gold;
extern void cpu_input_boost_kick_ufs(unsigned int duration_ms);
extern void cpu_input_boost_kick_flex(unsigned int duration_ms);
extern void cpu_input_boost_kick_core(unsigned int duration_ms, unsigned int cpu);
extern void cpu_input_boost_kick_cluster1(unsigned int duration_ms);
extern void cpu_input_boost_kick_cluster2(unsigned int duration_ms);
extern void cpu_input_boost_kick_cluster1_wake(unsigned int duration_ms);
extern void cpu_input_boost_kick_cluster2_wake(unsigned int duration_ms);
extern void gpu_boost_flex(unsigned int duration_ms);
extern unsigned int get_input_boost_freq(struct cpufreq_policy *policy);
extern unsigned int get_max_boost_freq(struct cpufreq_policy *policy);
extern unsigned int get_flex_boost_freq(struct cpufreq_policy *policy);
extern unsigned int get_min_freq(struct cpufreq_policy *policy);
#else
void cpu_input_boost_kick_ufs(unsigned int duration_ms)
{
}
void cpu_input_boost_kick_flex(unsigned int duration_ms)
{
}
void cpu_input_boost_kick_core(unsigned int duration_ms, unsigned int cpu)
{
}
void cpu_input_boost_kick_cluster1(unsigned int duration_ms)
{
}
void cpu_input_boost_kick_cluster2(unsigned int duration_ms)
{
}
void cpu_input_boost_kick_cluster1_wake(unsigned int duration_ms)
{
}
void cpu_input_boost_kick_cluster2_wake(unsigned int duration_ms)
{
}
void gpu_boost_flex(unsigned int duration_ms)
{
}
#endif

#endif /* _CPU_INPUT_BOOST_H_ */

