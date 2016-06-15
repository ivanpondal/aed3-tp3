#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

template <typename IN>
class experiment{
	public:
		virtual void init(const IN *input) = 0;
		virtual void run() = 0;
};

#endif // EXPERIMENT_H_INCLUDED
