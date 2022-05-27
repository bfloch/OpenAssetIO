{%   for line in copyright.split("\n") -%}
# {{ line }}
{% endfor -%}
"""
{{ description | wordwrap(72) }}
"""

from typing import Union

from openassetio import Trait

{% for traitId, trait in traits.items() %}

class {{ traitId[0] | upper }}{{ traitId[1:] }}Trait(Trait):
    """
    {{ trait.description | wordwrap(68) | indent(4) }}
    """
    kId = "{{ traitId }}.{{ package }}"

    {% if "properties" in trait -%}
        {% for name, property in trait["properties"].items() -%}
            {% set CamelCaseName = (name[0] | upper) + name[1:] -%}
    def set{{ CamelCaseName }}(self, {{ name }}: {{ property["type"] }}):
        """
        Sets the {{ name }}.

        {{ property["description"] | wordwrap(64) | indent(8) }}
        """
        if not isinstance({{ name }}, {{ property["type"] }}):
            raise TypeError("{{ name }} must be a {{ property["type"] }}")
        self._specification.setTraitProperty(self.kId, "{{ name }}", {{ name }})

    def get{{ CamelCaseName }}(self, defaultValue: {{ property["type"] }}=None) -> Union[{{ property["type"] }}, None]:
        """
        Gets the {{ name }}.

        {{ property["description"] | wordwrap(64) | indent(8) }}
        """
        value = self._specification.getTraitProperty(self.kId, "{{ name }}")
        if value is None:
            return defaultValue
        elif not isinstance(value, {{ property["type"] }}):
            if defaultValue is None:
                raise TypeError(f"Invalid stored value type: '{value}' [{type(value).__name__}]")
            return defaultValue
        return

        {%  endfor -%}
    {% endif -%}


{% endfor %}
