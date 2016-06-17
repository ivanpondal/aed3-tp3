#ifndef INCREMENTAL_EXPERIMENT_INPUT_H_
#define INCREMENTAL_EXPERIMENT_INPUT_H_

template <typename T, typename S>
class incremental_experiment_input{
	public:
		incremental_experiment_input(const T &min_val, const T &max_val,
		                             int discard_val, int repetitions_val,
		                             int samples_val, const S &subject_val,
		                             const char *exp_name){
			this->min_val = min_val;
			this->max_val = max_val;
			this->inc_val = min_val;
			this->discard_val = discard_val;
			this->repetitions_val = repetitions_val;
			this->samples_val = samples_val;
			this->subject_val = subject_val;
			this->exp_name = exp_name;
		};

		virtual ~incremental_experiment_input(){};

		void init(){
			delta_val = calculate_delta();
		}

		T get_min() const{
			return min_val;
		};

		T get_max() const{
			return max_val;
		};

		T &get_inc_val(){
			return inc_val;
		}

		T get_delta() const{
			return delta_val;
		}

		int get_discard() const{
			return discard_val;
		};

		int get_repetitions() const{
			return repetitions_val;
		};

		int get_samples() const{
			return samples_val;
		};

		S &get_subject(){
			return subject_val;
		}

		S &set_subject(const S &subject_val){
			this.subject_val = subject_val;
		}

		const char *get_exp_name() const{
			return exp_name;
		}

		virtual incremental_experiment_input<T, S> *clone() const = 0;
	private:
		virtual T calculate_delta() const = 0;
		T min_val;
		T max_val;
		T inc_val;
		T delta_val;
		int discard_val;
		int repetitions_val;
		int samples_val;
		S subject_val;
		const char *exp_name;
};

#endif // INCREMENTAL_EXPERIMENT_INPUT_H_INCLUDED
