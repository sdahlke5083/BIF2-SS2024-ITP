using Microsoft.EntityFrameworkCore;

namespace Geld_Guardian.Pages.Data.Models
{
    [PrimaryKey("StatusId")]
    public class PaymentStatus
    {
        public int StatusId { get; set; }
        public string Name { get; set; }
        
    }
}
