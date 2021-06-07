using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;
using UnityEngine.Events;
using System.Collections;

[RequireComponent(typeof(Button))]
public class ButtonUpDownHandler : MonoBehaviour, IPointerUpHandler, IPointerDownHandler, IPointerEnterHandler, IPointerExitHandler
{
    private Button m_button;

    public UnityEvent onPointerDown;
    public UnityEvent onPointerUp;
    public UnityEvent whilePointerPressed;

    private void Awake()
    {
        m_button = GetComponent<Button>();
    }

    private IEnumerator WhilePressed()
    {
        while (true)
        {
            whilePointerPressed?.Invoke();
            yield return null;
        }
    }
    public void OnPointerUp(PointerEventData eventData)
    {
        StopAllCoroutines();
        onPointerUp?.Invoke();
    }

    public void OnPointerDown(PointerEventData eventData)
    {
        if (!m_button.interactable) return;

        StopAllCoroutines();

        StartCoroutine(WhilePressed());

        onPointerDown?.Invoke();
    }

    public void OnPointerExit(PointerEventData eventData)
    {
        StopAllCoroutines();
        onPointerUp?.Invoke();
    }

    public void OnPointerEnter(PointerEventData eventData) { }
}
