#ifndef FUNCTION_H
#define FUNCTION_H

#include <memory>

namespace my {
    template<typename>
    class function;

    template<typename R, typename ...Args>
    class function<R(Args...)> {
    private:
        class functor {
        public:
            virtual ~functor() {};
            virtual R result(Args...) const = 0;
            virtual std::unique_ptr<functor> copy() const = 0;
        };

        template<typename T>
        class functor_impl : public functor {
        public:
            functor_impl(const T& t) : t(t) {}
            ~functor_impl() override = default;
            R result(Args... args) const override {
                return t(args...);
            }
            std::unique_ptr<functor> copy() const override {
                return std::make_unique<functor_impl<T>>(t);
            }
        private:
            T t;
        };
        std::unique_ptr<functor> func;
    public:
        function() noexcept {}

        template<typename F>
        function(F func) {
            this->func = std::make_unique<functor_impl<F>>(func);
        }

        function(std::nullptr_t) noexcept : func(nullptr) {}

        function(const function& other) : func(other.func->copy()) {}

        function(function&& other) noexcept : func(nullptr) {
            this->swap(other);
        }

        ~function() {}

        //TODO
        function& operator=(const function& other) {
            return *this;
        }

        function& operator=(function&& other) noexcept {
            this->swap(other);
            return *this;
        }

        /*
        template<typename F>
        function& operator=(F func) {
            this->func = std::make_unique<functor_impl<F>>(func);
            return *this;
        }
        */

        void swap(function& other) noexcept {
            std::swap(other.func, this->func);
        }

        explicit operator bool() const noexcept {
            return static_cast<bool>(func);
        }

        R operator()(Args... args) const {
            return func->result(args...);
        }
    };
}

#endif
