#ifndef SUBJECT
#define SUBJECT
#include <map>
#include <vector>
#include <functional>
#include <utility>

namespace game
{
	/*
	 *  Subject: accepts registration requests according to some key or event. Notifies observers registered for a given event.
	 *	Observers: register themselves to be notified by the observer for a given eventSubject
	 * 	Events: Act as registration key and trigger for notification
	 * 	
	 * 	Data and set data is used for shared data between components.
	 * 	
	 * 	Based on: https://github.com/juanchopanza/cppblog/blob/master/Patterns/Observer/
	 */

	// TODO: Feil i observer pattern- bruk delte data for kommunikasjon til dette prosjektet: endte med å bruke ResourceManager som hack.

	template <class Event>
	class ComponentCom
	{
	public:
		explicit ComponentCom();

		void set_data(const Event& event, int data);
		int data(const Event& event);

		template <typename Observer>
		void register_observer(const Event& event, Observer&& observer);

		template <typename Observer>
		void register_observer(Event&& event, Observer&& observer);

		void notify(const Event& event) const;

		// TODO: Add options to remove data and observers

		// Disallow copying and assigning
		//Subject(const Subject&) = delete;
		ComponentCom& operator=(const ComponentCom&) = delete;

	private:
		std::map<Event, std::vector<std::function<void()>>> observers_;
		std::map<Event, int> shared_int_; // Bind data to pull
	};

	// Implementation
	template <class Event>
	ComponentCom<Event>::ComponentCom()
	= default;

	template <class Event>
	void ComponentCom<Event>::set_data(const Event& event, int data)
	{
		shared_int_.insert_or_assign(event, data);
	}

	template <class Event>
	int ComponentCom<Event>::data(const Event& event)
	{
		return shared_int_.at(event);
	}

	template <class Event>
	template <typename Observer>
	void ComponentCom<Event>::register_observer(const Event& event, Observer&& observer)
	{
		observers_[event].push_back(std::forward<Observer>(observer));
	}

	template <class Event>
	template <typename Observer>
	void ComponentCom<Event>::register_observer(Event&& event, Observer&& observer)
	{
		observers_[std::move(event)].push_back(std::forward<Observer>(observer));
	}

	template <class Event>
	void ComponentCom<Event>::notify(const Event& event) const
	{
		for (const auto& event_receiver : observers_.at(event))
		{
			event_receiver();
		}
	}
}

#endif
